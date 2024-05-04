#define VAMP_LOGGER_INIT

#include "application.h"
#include <vamplogger/logger.h>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "layer.h"
#include "../debug/glcall.h"



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
        for (Layer *layer : m_layers)
        {
            layer->onDettach(this);
            delete layer;
        }

        delete m_window;

        VampDestroyLogger(VAMP_GLOBAL_ENGINE_LOGGER);
        VampDestroyLogger(VAMP_GLOBAL_CLIENT_LOGGER);
    }


    void Application::Run()
    {

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(m_window->m_window))
        {
            /* Render here */
            glCALL(glClear(GL_COLOR_BUFFER_BIT));

            this->processInput();

            for (Layer *layer : m_layers)
            {
                if ( !layer->m_hasStarted )
                {
                    layer->onStart(this);
                    layer->m_hasStarted = true;
                }

                layer->onUpdate(this);
            }

            m_window->update();
        }
    }


    void Application::processInput()
    {
        if (glfwGetKey(m_window->m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_window->m_window, 1);
        }
    }


    void Application::appendLayer(Layer *layer)
    {
        m_layers.push_back(layer);

        layer->onAttach(this);
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