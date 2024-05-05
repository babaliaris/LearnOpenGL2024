#include "colors.h"
#include "lighting_maps.h"
#include "cameraFunctionalityLayer.h"


namespace LearnOpenGL
{

    LightingMaps::LightingMaps(Application *app)
    : Layer("ColorsLayer", app), m_app(app),
      m_globalLightPos(4.0f, 2.0f, -4.0f)
    {
    }


    LightingMaps::~LightingMaps()
    {
        delete m_shaderObject;
        delete m_diffuse;
        delete m_specular;
    }


    void LightingMaps::onStart(Application *app)
    {
        m_camera = ((CameraFunctionalityLayer *)this->findLayer("CameraFunctionalityLayer"))->getCamera();

        this->PrepareVertexData();
    }


    void LightingMaps::onUpdate(Application *app)
    {
        m_shaderObject->SetUniform("view", m_camera->getView());
        m_shaderObject->SetUniform("u_CamPos", m_camera->getPosition());

        m_shaderLight->SetUniform("view", m_camera->getView());

        //Draw the Object.
        glCALL(glBindVertexArray(m_vaoObject));
        m_diffuse->Bind(0);
        m_specular->Bind(1);
        m_shaderObject->Bind();
        glCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
        m_shaderObject->Unbind();
        m_diffuse->UnBind();
        m_specular->UnBind();
        glCALL(glBindVertexArray(0));

        //Draw the Light.
        glCALL(glBindVertexArray(m_vaoLight));
        m_shaderLight->Bind();
        glCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
        m_shaderLight->Unbind();
        glCALL(glBindVertexArray(0));

        float lightZ = glm::cos(glm::radians(glfwGetTime())  * 100.0f) * m_globalLightPos.z;
        float lightX = glm::sin(glm::radians(glfwGetTime())  * 100.0f) * m_globalLightPos.z;
        glm::mat4 modelLight = glm::mat4(1.0f);
        modelLight = glm::translate(modelLight, glm::vec3(lightX, m_globalLightPos.y, lightZ));
        m_shaderLight->SetUniform("model", modelLight);

        m_shaderObject->SetUniform("u_placedLight.position", glm::vec3(lightX, m_globalLightPos.y, lightZ));

    }





    void LightingMaps::PrepareVertexData()
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
        glCALL(glGenVertexArrays(1, &m_vaoObject));
        glCALL(glBindVertexArray(m_vaoObject));

        glCALL(glGenBuffers(1, &m_vboObject));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vboObject));
        glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        glCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)0));
        glCALL(glEnableVertexAttribArray(0));

        glCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float) * 3)));
        glCALL(glEnableVertexAttribArray(1));

        glCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) (sizeof(float) * 6) ));
        glCALL(glEnableVertexAttribArray(2));

        glCALL(glBindVertexArray(0));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

        m_shaderObject = new LearnOpenGL::Shader("projects/LearnOpenGL/src/shaders/lightingWithMaps_vertex.glsl",
                                                "projects/LearnOpenGL/src/shaders/lightingWithMaps_fragment.glsl");
        

        //---------------Fragment Shader Uniforms Set---------------//

        //Material Properties.
        m_shaderObject->SetUniform("u_material.diffuse", 0);
        m_shaderObject->SetUniform("u_material.specular", 1);
        m_shaderObject->SetUniform("u_material.shininess", 32.0f);

        //Placed Light Properties.
        m_shaderObject->SetUniform("u_placedLight.position", m_globalLightPos);
        m_shaderObject->SetUniform("u_placedLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        m_shaderObject->SetUniform("u_placedLight.brightness", 1.0f);

        //Ambient Strength
        m_shaderObject->SetUniform("m_ambientFactor", 0.2f);

        //---------------Fragment Shader Uniforms Set---------------//

        m_diffuse   = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/diffuse_container.png");
        m_specular  = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/specular_container.png");

        glm::mat4 proj  = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat3 normalMat = glm::mat3(1.0f);

        proj = glm::perspective(
            glm::radians(45.0f),
            (float)m_app->getWindow()->getWidth() / m_app->getWindow()->getHeight(),
            0.1f,
            100.0f);

        normalMat = glm::mat3(glm::transpose(glm::inverse(model)));

        //Vertex Uniforms Set.
        m_shaderObject->SetUniform("proj", proj);
        m_shaderObject->SetUniform("model", model);
        m_shaderObject->SetUniform("normalMat", normalMat);
        //-----------------------------------Object Draw Call Preperation-----------------------------------//



        //-------------------------------Light Visuals Draw Call Preperation--------------------------------//
        glCALL(glGenVertexArrays(1, &m_vaoLight));
        glCALL(glBindVertexArray(m_vaoLight));

        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vboObject));

        glCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)0));
        glCALL(glEnableVertexAttribArray(0));

        glCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float) * 3)));
        glCALL(glEnableVertexAttribArray(1));

        glCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) (sizeof(float) * 6) ));
        glCALL(glEnableVertexAttribArray(2));

        glCALL(glBindVertexArray(0));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

        m_shaderLight = new LearnOpenGL::Shader("projects/LearnOpenGL/src/shaders/lightsource_vertex.glsl",
                                                "projects/LearnOpenGL/src/shaders/lightsource_fragment.glsl");

        glm::mat4 modelLight = glm::mat4(1.0f);
        modelLight = glm::translate(modelLight, m_globalLightPos);

        m_shaderLight->SetUniform("proj", proj);
        m_shaderLight->SetUniform("model", modelLight);
        //-------------------------------Light Visuals Draw Call Preperation--------------------------------//
    }

}