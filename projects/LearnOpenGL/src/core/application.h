#pragma once
#include <string>

namespace LearnOpenGL
{
    class Window;

    class Application
    {
        public:
        Application(const std::string &title, int width, int height);
        ~Application();

        void Run();

        private:
        Window *m_window;


        void processInput();

    };
}