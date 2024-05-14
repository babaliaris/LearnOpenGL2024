#pragma once

#include <string>
#include <glm/glm.hpp>

struct GLFWwindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

namespace LearnOpenGL
{
    class Window
    {
        friend class Application;
        friend void ::framebuffer_size_callback(GLFWwindow* window, int width, int height);
        
        public:
        Window(const std::string &title, int width, int height, int samples);
        ~Window();

        void update();
        void setClearColor(float r, float g, float b, float a);

        inline const std::string &getTitle() const {return m_title;}
        inline int getWidth() const {return m_width;}
        inline int getHeight() const {return m_height;}
        inline GLFWwindow *getGlfwWindow() const {return m_window;}
        inline glm::vec4 getClearColor() const {return m_clearColor;}

        private:
        std::string m_title;
        int m_width, m_height;
        GLFWwindow *m_window;
        glm::vec4 m_clearColor;
    };
}