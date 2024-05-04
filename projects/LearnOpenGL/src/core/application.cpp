#define VAMP_LOGGER_INIT

#include "application.h"
#include "window.h"
#include "../debug/glcall.h"
#include <vamplogger/logger.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <GLFW/glfw3.h>


#include "texture.h"
#include "shader.h"

namespace LearnOpenGL
{
    Application::Application(const std::string &title, int width, int height)
    {
        VAMP_GLOBAL_ENGINE_LOGGER = VampNewLogger("Engine");
        VAMP_GLOBAL_CLIENT_LOGGER = VampNewLogger("Client");

        m_window = new Window(title, width, height);
    }


    Application::~Application()
    {
        delete m_window;

        VampDestroyLogger(VAMP_GLOBAL_ENGINE_LOGGER);
        VampDestroyLogger(VAMP_GLOBAL_CLIENT_LOGGER);
    }


    void Application::Run()
    {


        float vertices[] = {
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
            0.0f, 0.5f, 0.0f,   0.5f, 1.0f,
        };

        unsigned int vao, vbo;

        glCALL(glGenVertexArrays(1, &vao));
        glCALL(glBindVertexArray(vao));

        glCALL(glGenBuffers(1, &vbo));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
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

        LearnOpenGL::Shader *shader = new LearnOpenGL::Shader(vertexPath.str().c_str(), fragmentPath.str().c_str());
        shader->SetUniform("m_texture", 0);

        LearnOpenGL::Texture *texture = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/wall.jpg");


        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view  = glm::mat4(1.0f);
        glm::mat4 proj  = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

        proj = glm::perspective(glm::radians(45.0f), (float)m_window->getWidth() / m_window->getHeight(), 0.1f, 100.0f);

        shader->SetUniform("model", model);
        shader->SetUniform("view", view);
        shader->SetUniform("proj", proj);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(m_window->m_window))
        {
            /* Render here */
            glCALL(glClear(GL_COLOR_BUFFER_BIT));

            this->processInput();

            //Render
            glCALL(glBindVertexArray(vao));
            shader->Bind();
            texture->Bind();
            glCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
            glCALL(glBindVertexArray(0));
            shader->Unbind();
            texture->UnBind();

            m_window->update();
        }

        delete shader;
        delete texture;
    }


    void Application::processInput()
    {
        if (glfwGetKey(m_window->m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_window->m_window, 1);
        }
    }
}



VampLogger *VampGlobalGetEngineLogger()
{
    return VAMP_GLOBAL_ENGINE_LOGGER;
}

VampLogger *VampGlobalGetClientLogger()
{
    return VAMP_GLOBAL_CLIENT_LOGGER;
}