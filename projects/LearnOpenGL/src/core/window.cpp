#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../debug/glcall.h"
#include <vamplogger/logger.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


namespace LearnOpenGL
{
    Window::Window(const std::string &title, int width, int height)
    : m_title(title), m_width(width), m_height(height), m_window(NULL)
    {
        /* Initialize the library */
        VAMP_INFO("[GLFW] Initializing GLFW...");
        if (!glfwInit())
        {
            VAMP_ERROR("[GLFW] GLFW failed to be initialized...");
            return;
        }

        //Window Hints.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* Create a windowed mode window and its OpenGL context */
        VAMP_INFO("[GLFW] Creating the window...");
        m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!m_window)
        {
            VAMP_ERROR("[GLFW] GLFW failed to create a window...");
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_window);

        //Initialize Glad.
        VAMP_INFO("[GLAD] Initializing GLAD...");
        if ( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) )
        {
            VAMP_ERROR("[GLAD] GLAD failed to be initialized...");
            glfwTerminate();
            return;
        }

        glCALL(glViewport(0, 0, m_width, m_height));

        glCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));


        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    }

    Window::~Window()
    {
        glfwTerminate();
    }


    void Window::update()
    {
        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    void Window::setClearColor(float r, float g, float b, float a)
    {
        glCALL(glClearColor(r, g, b, a));
    }
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glCALL(glViewport(0, 0, width, height));
}