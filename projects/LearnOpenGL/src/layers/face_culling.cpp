#include "face_culling.h"
#include "cameraFunctionalityLayer.h"

namespace LearnOpenGL
{
    FaceCulling::FaceCulling(Application *app)
    : Layer("ModelFullPhong", app), m_vaoCube(0), m_vboCube(0),
        m_vaoPlane(0), m_vboPlane(0),
        m_app(app)
    {
        m_directionalLight.direction    = glm::vec3(0.0f, -6.0f, -1.0f);
        m_directionalLight.diffuse      = glm::vec3(1.0f, 1.0f, 1.0f);
        m_directionalLight.brightness   = 1.0f;

        
        m_pointLight.position   = glm::vec3(0.0f, 2.0f, 4.0f);
        m_pointLight.diffuse    = glm::vec3(1.0f, 1.0f, 1.0f);
        m_pointLight.brightness = 1.0f;
        m_pointLight.attenuation= glm::vec3(1.0f, 0.09f, 0.032f);

        
        m_spotLight.diffuse     = glm::vec3(1.0f, 1.0f, 1.0f);
        m_spotLight.brightness  = 1.0f;
        m_spotLight.attenuation = glm::vec3(1.0f, 0.09f, 0.032f);
        m_spotLight.cutoff      = glm::cos(glm::radians(12.0f));
        m_spotLight.outer       = glm::cos(glm::radians(15.0f));
    }


    FaceCulling::~FaceCulling()
    {
        delete m_shader;
        delete m_cubeDiffuse;
        delete m_cubeSpecular;

    }


    void FaceCulling::onStart(Application *app)
    {
        m_camera = ((CameraFunctionalityLayer *)this->findLayer("CameraFunctionalityLayer"))->getCamera();

        this->PrepareCubeData();
        this->PreparePlaneData();

        m_cubePositions = {
            { 0.0f, 0.8f, -20.0f},
            { -4.0f, 0.8f, -12.0f},
            {-8.0f, 0.8f, -20.0f},
            { 8.0f, 0.8f, -20.0f},
        };

        m_grassPositions = {
            { 0.0f, 0.8f, -30.0f},
            { -6.0f, 0.8f, -12.0f},
            {-6.0f, 0.8f, -25.0f},
            { 6.0f, 0.8f, -15.0f},
        };

        m_windowPositions = {
            { 0.0f, 0.8f, -28.0f},
            { -6.0f, 0.8f, -14.0f},
            {-6.0f, 0.8f, -23.0f},
            { 6.0f, 0.8f, -12.0f},
        };
    }


    void FaceCulling::onUpdate(Application *app)
    {
        
        m_shader->SetUniform("u_proj", glm::perspective(glm::radians(45.0f), 
        app->getWindow()->getWidth() / (float)app->getWindow()->getHeight(), 0.1f, 100.0f));

        m_shader->SetUniform("u_view", m_camera->getView());

        m_shader->SetUniform("u_CamPos", m_camera->getPosition());

        m_shader->SetUniform("u_spotLight.direction", m_camera->getForward());
        m_shader->SetUniform("u_spotLight.position", m_camera->getPosition());


        //Render the floor.
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f));
        model = glm::scale(model, glm::vec3(20.0f, 0.5f, 20.0f));
        m_shader->SetUniform("u_model", model);
        m_shader->SetUniform("u_normal", glm::transpose(glm::inverse(model)));
        this->RenderCube();

        //Render some cubes.
        for (glm::vec3 position : m_cubePositions)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            m_shader->SetUniform("u_model", model);
            m_shader->SetUniform("u_normal", glm::transpose(glm::inverse(model)));
            this->RenderCube();
        }

        for (glm::vec3 position : m_grassPositions)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            m_shader->SetUniform("u_model", model);
            m_shader->SetUniform("u_normal", glm::transpose(glm::inverse(model)));
            this->RenderPlane(true);
        }


        for (glm::vec3 position : m_windowPositions)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            m_shader->SetUniform("u_model", model);
            m_shader->SetUniform("u_normal", glm::transpose(glm::inverse(model)));
            this->RenderPlane(false);
        }

    }


    void FaceCulling::PrepareCubeData()
    {
        float vertices[] = {
            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f, // bottom-right         
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // top-right
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, // bottom-left
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f, // top-left
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom-left
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // bottom-right
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top-right
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top-right
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // top-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom-left
            // Left face
            -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // top-right
            -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top-left
            -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // bottom-right
            -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // top-right
            // Right face
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // top-left
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // bottom-right
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top-right         
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // bottom-right
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // top-left
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // bottom-left     
            // Bottom face
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f, // top-left
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f, // bottom-left
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f, // top-right
            // Top face
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top-left
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom-right
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // top-right
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom-right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top-left
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f  // bottom-left
        };


        //-----------------------------------Object Draw Call Preperation-----------------------------------//
        glCALL(glGenVertexArrays(1, &m_vaoCube));
        glCALL(glBindVertexArray(m_vaoCube));

        glCALL(glGenBuffers(1, &m_vboCube));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vboCube));
        glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        glCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)0));
        glCALL(glEnableVertexAttribArray(0));

        glCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float) * 3)));
        glCALL(glEnableVertexAttribArray(1));

        glCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) (sizeof(float) * 6) ));
        glCALL(glEnableVertexAttribArray(2));

        glCALL(glBindVertexArray(0));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));


        m_cubeDiffuse   = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/diffuse_container.png");
        m_cubeSpecular  = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/specular_container.png");
        //-----------------------------------Object Draw Call Preperation-----------------------------------//


        m_shader = new Shader("projects/LearnOpenGL/src/shaders/phong_vertex.glsl",
        "projects/LearnOpenGL/src/shaders/phong_fragment.glsl");


        m_shader->SetUniform("u_enableObjectOutline", 0);

        m_shader->SetUniform("u_ambientFactor", 0.1f);
        m_shader->SetUniform("u_numberOfDirectionalLights", 1);
        m_shader->SetUniform("u_numberOfPointLights", 1);
        m_shader->SetUniform("u_numberOfSpotLights", 1);

        //Directional Light Properties.
        m_shader->SetUniform("u_directionalLight.direction", m_directionalLight.direction);
        m_shader->SetUniform("u_directionalLight.diffuse", m_directionalLight.diffuse);
        m_shader->SetUniform("u_directionalLight.brightness", m_directionalLight.brightness);

        
        //Point Light Properties.
        m_shader->SetUniform("u_pointLight.position", m_pointLight.position);
        m_shader->SetUniform("u_pointLight.diffuse", m_pointLight.diffuse);
        m_shader->SetUniform("u_pointLight.brightness", m_pointLight.brightness);
        m_shader->SetUniform("u_pointLight.attenuation", m_pointLight.attenuation);

        
        //Spot Light Properties.
        m_shader->SetUniform("u_spotLight.diffuse", m_spotLight.diffuse);
        m_shader->SetUniform("u_spotLight.brightness", m_spotLight.brightness);
        m_shader->SetUniform("u_spotLight.attenuation", m_spotLight.attenuation);
        m_shader->SetUniform("u_spotLight.cutoff", m_spotLight.cutoff);
        m_shader->SetUniform("u_spotLight.outer", m_spotLight.outer);
    }


    void FaceCulling::PreparePlaneData()
    {
        float vertices[] = {
            // positions          // normals           // texture coords
           -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,

           -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
           -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f
        };

        //-----------------------------------Object Draw Call Preperation-----------------------------------//
        glCALL(glGenVertexArrays(1, &m_vaoPlane));
        glCALL(glBindVertexArray(m_vaoPlane));

        glCALL(glGenBuffers(1, &m_vboPlane));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vboPlane));
        glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        glCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)0));
        glCALL(glEnableVertexAttribArray(0));

        glCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float) * 3)));
        glCALL(glEnableVertexAttribArray(1));

        glCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) (sizeof(float) * 6) ));
        glCALL(glEnableVertexAttribArray(2));

        glCALL(glBindVertexArray(0));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        //-----------------------------------Object Draw Call Preperation-----------------------------------//

        m_windowTexture = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/window.png");
        m_grassTexture  = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/grass.png");
    }


    void FaceCulling::RenderCube()
    {
        glCALL(glBindVertexArray(m_vaoCube));
        m_cubeDiffuse->Bind(0);
        m_cubeSpecular->Bind(1);
        m_shader->SetUniform("u_material.diffuse0", 0);
        m_shader->SetUniform("u_material.specular0", 1);
        m_shader->SetUniform("u_material.numOfDiffuse", 1);
        m_shader->SetUniform("u_material.numOfSpecular", 1);
        m_shader->Bind();
        glCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
        glCALL(glBindVertexArray(0));
        m_cubeDiffuse->UnBind();
        m_cubeSpecular->UnBind();
    }


    void FaceCulling::RenderPlane(bool isGrass)
    {
        glCALL(glBindVertexArray(m_vaoPlane));

        if (isGrass)
        {
            m_grassTexture->Bind(0);
        }

        else
        {
            m_windowTexture->Bind(0);
        }

        m_shader->SetUniform("u_material.diffuse0", 0);
        m_shader->SetUniform("u_material.numOfDiffuse", 1);
        m_shader->SetUniform("u_material.numOfSpecular", 0);

        m_shader->Bind();
        glCALL(glDrawArrays(GL_TRIANGLES, 0, 6));

        glCALL(glBindVertexArray(0));
        m_grassTexture->UnBind();
        m_windowTexture->UnBind();
    }
}