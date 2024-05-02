#define VAMP_LOGGER_INIT

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vamplogger/logger.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main(void)
{
    VAMP_GLOBAL_ENGINE_LOGGER = VampNewLogger("Engine");
    VAMP_GLOBAL_CLIENT_LOGGER = VampNewLogger("Client");

    GLFWwindow* window;

    /* Initialize the library */
    VAMP_INFO("[GLFW] Initializing GLFW...");
    if (!glfwInit())
    {
        VAMP_ERROR("[GLFW] GLFW failed to be initialized...");
        VampDestroyLogger(VAMP_GLOBAL_ENGINE_LOGGER);
        VampDestroyLogger(VAMP_GLOBAL_CLIENT_LOGGER);
        return -1;
    }

    //Window Hints.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    VAMP_INFO("[GLFW] Creating the window...");
    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        VAMP_ERROR("[GLFW] GLFW failed to create a window...");
        glfwTerminate();
        VampDestroyLogger(VAMP_GLOBAL_ENGINE_LOGGER);
        VampDestroyLogger(VAMP_GLOBAL_CLIENT_LOGGER);
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //Initialize Glad.
    VAMP_INFO("[GLAD] Initializing GLAD...");
    if ( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) )
    {
        VAMP_ERROR("[GLAD] GLAD failed to be initialized...");
        glfwTerminate();
        VampDestroyLogger(VAMP_GLOBAL_ENGINE_LOGGER);
        VampDestroyLogger(VAMP_GLOBAL_CLIENT_LOGGER);
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    VampDestroyLogger(VAMP_GLOBAL_ENGINE_LOGGER);
    VampDestroyLogger(VAMP_GLOBAL_CLIENT_LOGGER);
    return 0;
}





void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}





void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}





VampLogger *VampGlobalGetEngineLogger()
{
    return VAMP_GLOBAL_ENGINE_LOGGER;
}

VampLogger *VampGlobalGetClientLogger()
{
    return VAMP_GLOBAL_CLIENT_LOGGER;
}