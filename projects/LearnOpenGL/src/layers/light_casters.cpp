#include "colors.h"
#include "light_casters.h"
#include "cameraFunctionalityLayer.h"


/**
 * Keyboard Binds
 * Number 1: Reduce directional light brightness.
 * Number 2: Increase directional light brightness.
 * Number 3: Reduce point light brightness.
 * Number 4: Increase point light brightness.
*/


namespace LearnOpenGL
{

    LightingCasters::LightingCasters(Application *app)
    : Layer("ColorsLayer", app), m_app(app)
    {
        m_directionalLight.direction    = glm::vec3(0.0f, -4.0f, -1.0f);
        m_directionalLight.diffuse      = glm::vec3(1.0f, 1.0f, 1.0f);
        m_directionalLight.brightness   = 0.0f;

        m_pointLight.position   = glm::vec3(0.0f, 0.0f, 4.0f);
        m_pointLight.diffuse    = glm::vec3(1.0f, 1.0f, 1.0f);
        m_pointLight.brightness = 0.0f;
        m_pointLight.attenuation= glm::vec3(1.0f, 0.09f, 0.032f);

        m_spotLight.diffuse     = glm::vec3(1.0f, 1.0f, 1.0f);
        m_spotLight.brightness  = 1.0f;
        m_spotLight.attenuation = glm::vec3(1.0f, 0.09f, 0.032f);
        m_spotLight.cutoff      = glm::cos(glm::radians(12.0f));
        m_spotLight.outer       = glm::cos(glm::radians(15.0f));

    }


    LightingCasters::~LightingCasters()
    {
        delete m_shaderObject;
        delete m_diffuse;
        delete m_specular;

        glCALL(glDeleteVertexArrays(1, &m_vaoObject));
        glCALL(glDeleteBuffers(1, &m_vboObject));
    }


    void LightingCasters::onStart(Application *app)
    {
        m_camera = ((CameraFunctionalityLayer *)this->findLayer("CameraFunctionalityLayer"))->getCamera();

        this->PrepareVertexData();

        m_cubePositions[0] = glm::vec3( 0.0f,  0.0f,  0.0f);
        m_cubePositions[1] = glm::vec3( 2.0f,  5.0f, -15.0f);
        m_cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
        m_cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
        m_cubePositions[4] = glm::vec3( 2.4f, -0.4f, -3.5f);
        m_cubePositions[5] = glm::vec3(-1.7f,  3.0f, -7.5f);
        m_cubePositions[6] = glm::vec3( 1.3f, -2.0f, -2.5f);
        m_cubePositions[7] = glm::vec3( 1.5f,  2.0f, -2.5f);
        m_cubePositions[8] = glm::vec3( 1.5f,  0.2f, -1.5f);
        m_cubePositions[9] = glm::vec3(-1.3f,  1.0f, -1.5f);
    }



    void LightingCasters::onUpdate(Application *app)
    {
        this->ProcessInput();

        m_shaderObject->SetUniform("view", m_camera->getView());
        m_shaderObject->SetUniform("u_CamPos", m_camera->getPosition());

        m_spotLight.position    = m_camera->getPosition();
        m_spotLight.direction   = m_camera->getForward();
        m_shaderObject->SetUniform("u_spotLight.position", m_spotLight.position);
        m_shaderObject->SetUniform("u_spotLight.direction", m_spotLight.direction);

        //Draw the Objects.
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat3 normalMat = glm::mat3(1.0f);
            model = glm::translate(model, m_cubePositions[i]);
            float angle = 20.0f * i; 
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            normalMat = glm::mat3(glm::transpose(glm::inverse(model)));
            m_shaderObject->SetUniform("model", model);
            m_shaderObject->SetUniform("normalMat", normalMat);

            //Draw the cubes.
            glCALL(glBindVertexArray(m_vaoObject));
            m_diffuse->Bind(0);
            m_specular->Bind(1);
            m_shaderObject->Bind();
            glCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
            glCALL(glBindVertexArray(0));
            m_shaderObject->Unbind();
            m_diffuse->UnBind();
            m_specular->UnBind();
        }

    }





    void LightingCasters::PrepareVertexData()
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

        m_shaderObject = new LearnOpenGL::Shader("projects/LearnOpenGL/src/shaders/light_casters_vertex.glsl",
                                                "projects/LearnOpenGL/src/shaders/light_casters_fragment.glsl");
        

        //---------------Fragment Shader Uniforms Set---------------//

        //Material Properties.
        m_shaderObject->SetUniform("u_material.diffuse", 0);
        m_shaderObject->SetUniform("u_material.specular", 1);
        m_shaderObject->SetUniform("u_material.shininess", 32.0f);

        //Directional Light Properties.
        m_shaderObject->SetUniform("u_directionalLight.direction", m_directionalLight.direction);
        m_shaderObject->SetUniform("u_directionalLight.diffuse", m_directionalLight.diffuse);
        m_shaderObject->SetUniform("u_directionalLight.brightness", m_directionalLight.brightness);


        //Point Light Properties.
        m_shaderObject->SetUniform("u_pointLight.position", m_pointLight.position);
        m_shaderObject->SetUniform("u_pointLight.diffuse", m_pointLight.diffuse);
        m_shaderObject->SetUniform("u_pointLight.brightness", m_pointLight.brightness);
        m_shaderObject->SetUniform("u_pointLight.attenuation", m_pointLight.attenuation);


        //Spot Light Properties.
        m_shaderObject->SetUniform("u_spotLight.diffuse", m_spotLight.diffuse);
        m_shaderObject->SetUniform("u_spotLight.brightness", m_spotLight.brightness);
        m_shaderObject->SetUniform("u_spotLight.attenuation", m_spotLight.attenuation);
        m_shaderObject->SetUniform("u_spotLight.cutoff", m_spotLight.cutoff);
        m_shaderObject->SetUniform("u_spotLight.outer", m_spotLight.outer);



        //Ambient Strength
        m_shaderObject->SetUniform("u_ambientFactor", 0.1f);

        //---------------Fragment Shader Uniforms Set---------------//

        m_diffuse   = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/diffuse_container.png");
        m_specular  = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/specular_container.png");

        glm::mat4 proj  = glm::mat4(1.0f);

        proj = glm::perspective(
            glm::radians(45.0f),
            (float)m_app->getWindow()->getWidth() / m_app->getWindow()->getHeight(),
            0.1f,
            100.0f);

        //Vertex Uniforms Set.
        m_shaderObject->SetUniform("proj", proj);
        //-----------------------------------Object Draw Call Preperation-----------------------------------//
    }



    void LightingCasters::ProcessInput()
    {
        GLFWwindow *window = m_app->getWindow()->getGlfwWindow();

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            m_directionalLight.brightness += 0.01;
            m_directionalLight.brightness = m_directionalLight.brightness > 1 ? 1 : m_directionalLight.brightness;
            m_shaderObject->SetUniform("u_directionalLight.brightness", m_directionalLight.brightness);
        }

        else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            m_directionalLight.brightness -= 0.01;
            m_directionalLight.brightness = m_directionalLight.brightness < 0 ? 0 : m_directionalLight.brightness;
            m_shaderObject->SetUniform("u_directionalLight.brightness", m_directionalLight.brightness);
        }


        else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        {
            m_pointLight.brightness += 0.01;
            m_pointLight.brightness = m_pointLight.brightness > 1 ? 1 : m_pointLight.brightness;
            m_shaderObject->SetUniform("u_pointLight.brightness", m_pointLight.brightness);
        }

        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        {
            m_pointLight.brightness -= 0.01;
            m_pointLight.brightness = m_pointLight.brightness < 0 ? 0 : m_pointLight.brightness;
            m_shaderObject->SetUniform("u_pointLight.brightness", m_pointLight.brightness);
        }


        else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        {
            m_spotLight.brightness += 0.01;
            m_spotLight.brightness = m_spotLight.brightness > 1 ? 1 : m_spotLight.brightness;
            m_shaderObject->SetUniform("u_spotLight.brightness", m_spotLight.brightness);
        }

        else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        {
            m_spotLight.brightness -= 0.01;
            m_spotLight.brightness = m_spotLight.brightness < 0 ? 0 : m_spotLight.brightness;
            m_shaderObject->SetUniform("u_spotLight.brightness", m_spotLight.brightness);
        }

        else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        {
            m_pointLight.attenuation.y -= 0.01;
            m_pointLight.attenuation.z -= 0.001;
            m_spotLight.attenuation.y  -= 0.01;
            m_spotLight.attenuation.z  -= 0.001;

            m_pointLight.attenuation.y = m_pointLight.attenuation.y < 0 ? 0 : m_pointLight.attenuation.y;
            m_pointLight.attenuation.z = m_pointLight.attenuation.z < 0 ? 0 : m_pointLight.attenuation.z;
            m_spotLight.attenuation.y = m_spotLight.attenuation.y < 0 ? 0 : m_spotLight.attenuation.y;
            m_spotLight.attenuation.z = m_spotLight.attenuation.z < 0 ? 0 : m_spotLight.attenuation.z;

            m_shaderObject->SetUniform("u_pointLight.attenuation", m_pointLight.attenuation);
            m_shaderObject->SetUniform("u_spotLight.attenuation", m_spotLight.attenuation);
        }

        else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        {
            m_pointLight.attenuation.y += 0.01;
            m_pointLight.attenuation.z += 0.001;
            m_spotLight.attenuation.y  += 0.01;
            m_spotLight.attenuation.z  += 0.001;
            m_shaderObject->SetUniform("u_pointLight.attenuation", m_pointLight.attenuation);
            m_shaderObject->SetUniform("u_spotLight.attenuation", m_spotLight.attenuation);
        }
    }

}