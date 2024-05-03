#define VAMP_LOGGER_INIT

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vamplogger/logger.h>
#include "debug/glcall.h"
#include "core/shader.h"
#include "core/texture.h"
#include <iostream>
#include <sstream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void cleanUp();







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
        cleanUp();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //Initialize Glad.
    VAMP_INFO("[GLAD] Initializing GLAD...");
    if ( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) )
    {
        VAMP_ERROR("[GLAD] GLAD failed to be initialized...");
        cleanUp();
        return -1;
    }

    glCALL(glViewport(0, 0, 800, 600));

    glCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


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
    vertexPath << "projects/LearnOpenGL/src/shaders/texture_vertex.glsl";
    fragmentPath << "projects/LearnOpenGL/src/shaders/texture_fragment.glsl";

    LearnOpenGL::Shader *shader = new LearnOpenGL::Shader(vertexPath.str().c_str(), fragmentPath.str().c_str());
    shader->SetUniform("m_texture", 0);

    LearnOpenGL::Texture *texture = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/wall.jpg");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glCALL(glClear(GL_COLOR_BUFFER_BIT));

        processInput(window);

        //Render
        glCALL(glBindVertexArray(vao));
        shader->Bind();
        texture->Bind();
        glCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
        glCALL(glBindVertexArray(0));
        shader->Unbind();
        texture->UnBind();
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete shader;
    delete texture;

    cleanUp();
    return 0;
}





void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}





void cleanUp()
{
    VAMP_INFO("[LearnOpenGL] Cleaning Up...");
    glfwTerminate();
    VampDestroyLogger(VAMP_GLOBAL_ENGINE_LOGGER);
    VampDestroyLogger(VAMP_GLOBAL_CLIENT_LOGGER);
    VAMP_INFO("[LearnOpenGL] Good Bye :)");
}





void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glCALL(glViewport(0, 0, width, height));
}





VampLogger *VampGlobalGetEngineLogger()
{
    return VAMP_GLOBAL_ENGINE_LOGGER;
}

VampLogger *VampGlobalGetClientLogger()
{
    return VAMP_GLOBAL_CLIENT_LOGGER;
}