#pragma once
#include <string>
#include <vector>

namespace LearnOpenGL
{
    class Window;
    class Layer;

    class Application
    {
        public:
        Application(const std::string &title, int width, int height);
        ~Application();

        void Run();

        void appendLayer(Layer *layer);

        inline Window *getWindow() const {return m_window;}
        inline float getDeltaTime() const {return m_deltaTime;}

        private:
        Window *m_window;
        std::vector<Layer *> m_layers;
        float m_deltaTime;


        void processInput();

    };
}