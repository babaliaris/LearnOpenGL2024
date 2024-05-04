#pragma once

#include <string>

struct GLFWwindow;

namespace LearnOpenGL
{
    class Window
    {
        friend class Application;
        
        public:
        Window(const std::string &title, int width, int height);
        ~Window();

        void update();
        void setClearColor(float r, float g, float b, float a);

        inline const std::string &getTitle() const {return m_title;}
        inline int getWidth() const {return m_width;}
        inline int getHeight() const {return m_height;}
        inline GLFWwindow *getGlfwWindow() const {return m_window;}

        private:
        std::string m_title;
        int m_width, m_height;
        GLFWwindow *m_window;
    };
}