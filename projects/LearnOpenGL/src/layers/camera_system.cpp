#include "camera_system.h"


namespace LearnOpenGL
{

    CameraSystem::CameraSystem()
    : Layer("CameraSystem"), m_shader(nullptr), m_texture(nullptr), m_vao(0), m_vbo(0),
        m_moveSpeed(10.0f)
    {
    }


    CameraSystem::~CameraSystem()
    {
        delete m_camera;
        delete m_shader;
        delete m_texture;
    }


    void CameraSystem::onStart(Application *app)
    {
        m_camera = new Camera3D(app, glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        m_camera->simulateFPS();

        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };



        glCALL(glGenVertexArrays(1, &m_vao));
        glCALL(glBindVertexArray(m_vao));

        glCALL(glGenBuffers(1, &m_vbo));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
        glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        glCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void *)0));
        glCALL(glEnableVertexAttribArray(0));

        glCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void *) (sizeof(float) * 3) ));
        glCALL(glEnableVertexAttribArray(1));

        glCALL(glBindVertexArray(0));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

        std::stringstream vertexPath, fragmentPath;
        vertexPath << "projects/LearnOpenGL/src/shaders/mvp_vertex.glsl";
        fragmentPath << "projects/LearnOpenGL/src/shaders/texture_fragment.glsl";

        m_shader = new LearnOpenGL::Shader(vertexPath.str().c_str(), fragmentPath.str().c_str());
        m_shader->SetUniform("m_texture", 0);

        m_texture = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/wall.jpg");

        glm::mat4 proj  = glm::mat4(1.0f);

        proj = glm::perspective(
            glm::radians(45.0f),
            (float)app->getWindow()->getWidth() / app->getWindow()->getHeight(),
            0.1f,
            100.0f);


        m_shader->SetUniform("proj", proj);


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


    void CameraSystem::onUpdate(Application *app)
    {
        this->processInput(app->getWindow()->getGlfwWindow(), app);

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_cubePositions[i]);
            float angle = 20.0f * i; 
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_shader->SetUniform("model", model);

            //Draw the cubes.
            glCALL(glBindVertexArray(m_vao));
            m_shader->Bind();
            m_texture->Bind();
            glCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
            glCALL(glBindVertexArray(0));
            m_shader->Unbind();
            m_texture->UnBind();
        }

        m_shader->SetUniform("view", m_camera->getView());
    }


    void CameraSystem::processInput(GLFWwindow *window, Application *app)
    {
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            m_camera->move( m_camera->getForward(), m_moveSpeed * app->getDeltaTime());
        }


        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            m_camera->move( -m_camera->getForward(), m_moveSpeed * app->getDeltaTime());
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            m_camera->move( -m_camera->getRight(), m_moveSpeed * app->getDeltaTime());
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_camera->move( m_camera->getRight(), m_moveSpeed * app->getDeltaTime());
        }
        
    }

}