#include "colors.h"
#include "cameraFunctionalityLayer.h"


namespace LearnOpenGL
{

    ColorsLayer::ColorsLayer(Application *app)
    : Layer("ColorsLayer", app),
      m_globalLightPos(4.0f, 2.0f, -4.0f)
    {
    }


    ColorsLayer::~ColorsLayer()
    {
        delete m_shaderObject;
        delete m_texture;
    }


    void ColorsLayer::onStart(Application *app)
    {
        m_camera = ((CameraFunctionalityLayer *)this->findLayer("CameraFunctionalityLayer"))->getCamera();


        

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

        m_shaderObject = new LearnOpenGL::Shader("projects/LearnOpenGL/src/shaders/lighting_vertex.glsl",
                                                "projects/LearnOpenGL/src/shaders/lighting_fragment.glsl");
        
        m_shaderObject->SetUniform("m_texture", 0);

        m_texture = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/wall.jpg");

        glm::mat4 proj  = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat3 normalMat = glm::mat3(1.0f);

        proj = glm::perspective(
            glm::radians(45.0f),
            (float)app->getWindow()->getWidth() / app->getWindow()->getHeight(),
            0.1f,
            100.0f);

        normalMat = glm::mat3(glm::transpose(glm::inverse(model)));

        m_shaderObject->SetUniform("proj", proj);
        m_shaderObject->SetUniform("model", model);
        m_shaderObject->SetUniform("normalMat", normalMat);
        m_shaderObject->SetUniform("m_LightPos", m_globalLightPos);



        glCALL(glGenVertexArrays(1, &m_vaoLight));
        glCALL(glBindVertexArray(m_vaoLight));

        glCALL(glGenBuffers(1, &m_vboLight));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vboLight));
        glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

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
    }


    void ColorsLayer::onUpdate(Application *app)
    {
        m_shaderObject->SetUniform("view", m_camera->getView());
        m_shaderObject->SetUniform("m_CamPos", m_camera->getPosition());

        m_shaderLight->SetUniform("view", m_camera->getView());

        //Draw the Object.
        glCALL(glBindVertexArray(m_vaoObject));
        m_texture->Bind();
        m_shaderObject->Bind();
        glCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
        m_shaderObject->Unbind();
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

        m_shaderObject->SetUniform("m_LightPos", glm::vec3(lightX, m_globalLightPos.y, lightZ));

    }

}