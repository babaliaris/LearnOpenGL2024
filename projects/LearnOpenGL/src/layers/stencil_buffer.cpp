#include "stencil_buffer.h"
#include "cameraFunctionalityLayer.h"

namespace LearnOpenGL
{
    StencilBuffer::StencilBuffer(Application *app)
    : Layer("ModelFullPhong", app), m_vaoCube(0), m_vboCube(0), m_app(app), m_model(nullptr)
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


    StencilBuffer::~StencilBuffer()
    {
        delete m_model;
        delete m_shader;
        delete m_cubeDiffuse;
        delete m_cubeSpecular;

    }


    void StencilBuffer::onStart(Application *app)
    {
        m_camera = ((CameraFunctionalityLayer *)this->findLayer("CameraFunctionalityLayer"))->getCamera();

        this->PrepareModel(); //Also creates the shader.
        this->PrepareCubeData(); //Uses the above shader.
    }


    void StencilBuffer::onUpdate(Application *app)
    {
        
        m_shader->SetUniform("u_proj", glm::perspective(glm::radians(45.0f), 
        app->getWindow()->getWidth() / (float)app->getWindow()->getHeight(), 0.1f, 100.0f));

        m_shader->SetUniform("u_view", m_camera->getView());

        m_shader->SetUniform("u_CamPos", m_camera->getPosition());

        m_shader->SetUniform("u_spotLight.direction", m_camera->getForward());
        m_shader->SetUniform("u_spotLight.position", m_camera->getPosition());
        
        
        //Prepare stencil buffer for writting with 1s when the depth test passes.
        glCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF)); //Make sure stencil always passes.
        glCALL(glStencilMask(0xFF)); //Enable stencil writting.
        glCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE)); //Replace with 1 if depth passes.
        m_shader->SetUniform("u_enableObjectOutline", 0); //Phong lighting model.

        //Render the model.
        if (m_model) m_model->Draw(m_shader);

        //Disable stencil writting and prepare for comparizon.
        glCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF)); //If stencil values != 1, pass and draw the outline.
        glCALL(glStencilMask(0x00)); //Disable stencil writting.
        glCALL(glDisable(GL_DEPTH_TEST)); //Disable depth test so that the outline will not be overitten.

        //Draw the scaled model and enable outline mode in the shader.
        glm::mat4 modelModelMat = glm::mat4(1.0f);
        modelModelMat = glm::scale(modelModelMat, glm::vec3(1.1f, 1.1f, 1.1f));
        m_shader->SetUniform("u_enableObjectOutline", 1);
        m_shader->SetUniform("u_model", modelModelMat);
        if (m_model) m_model->Draw(m_shader);
        m_shader->SetUniform("u_model", glm::mat4(1.0f));

        //Re-enable phong model and disable stencil by let in it to always pass.
        m_shader->SetUniform("u_enableObjectOutline", 0);
        glCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
        glCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP));
        glCALL(glEnable(GL_DEPTH_TEST)); //Enable depth test.

       //Prepare stencil buffer for writting with 1s when the depth test passes.
        glCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF)); //Make sure stencil always passes.
        glCALL(glStencilMask(0xFF)); //Enable stencil writting.
        glCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE)); //Replace with 1 if depth passes.
        m_shader->SetUniform("u_enableObjectOutline", 0); //Phong lighting model.
        glm::mat4 cubeModel = glm::mat4(1.0f);
        cubeModel = glm::translate(cubeModel, glm::vec3(4.0f, 0.0f, 0.0f));
        m_shader->SetUniform("u_model", cubeModel);
        m_shader->SetUniform("u_normal", glm::transpose(glm::inverse(cubeModel)));
        this->RenderCube();
        m_shader->SetUniform("u_normal", glm::mat4(1.0f)); //Reset the normal mat for the model to be rendered at without any tranforms.


        //Disable stencil writting and prepare for comparizon.
        glCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF)); //If stencil values != 1, pass and draw the outline.
        glCALL(glStencilMask(0x00)); //Disable stencil writting.
        glCALL(glDisable(GL_DEPTH_TEST)); //Disable depth test so that the outline will not be overitten.

        //Draw the scaled model and enable outline mode in the shader.
        cubeModel = glm::scale(cubeModel, glm::vec3(1.1f, 1.1f, 1.1f));
        m_shader->SetUniform("u_enableObjectOutline", 1);
        m_shader->SetUniform("u_model", cubeModel);
        this->RenderCube();
        m_shader->SetUniform("u_model", glm::mat4(1.0f));

        //Re-enable phong model and disable stencil by let in it to always pass.
        m_shader->SetUniform("u_enableObjectOutline", 0);
        glCALL(glStencilFunc(GL_ALWAYS, 0, 0xFF));
        glCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP));
        glCALL(glStencilMask(0xFF)); //Enable stencil writting for the glClear(GL_STENCIL_BUFFER_BIT) to have access to write in it.
        glCALL(glEnable(GL_DEPTH_TEST)); //Enable depth test.

    }


    void StencilBuffer::PrepareModel()
    {
        m_shader = new Shader("projects/LearnOpenGL/src/shaders/phong_vertex.glsl",
        "projects/LearnOpenGL/src/shaders/phong_fragment.glsl");

        glm::mat4 model     = glm::mat4(1.0f);
        glm::mat4 normal    = glm::mat4(1.0f);
        normal              = glm::transpose(glm::inverse(model));

        m_shader->SetUniform("u_model", model);
        m_shader->SetUniform("u_normal", normal);
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

        m_model = new Model("projects/LearnOpenGL/resources/models/backpack/backpack.obj");
    }


    void StencilBuffer::PrepareCubeData()
    {
        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
    }


    void StencilBuffer::RenderCube()
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
}