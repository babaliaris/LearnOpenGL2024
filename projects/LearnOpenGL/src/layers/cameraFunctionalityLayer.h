#pragma once
#include "../core/learnOpenGL.h"

struct GLFWwindow;

namespace LearnOpenGL
{
    class CameraFunctionalityLayer : public LearnOpenGL::Layer
    {
        public:
        CameraFunctionalityLayer(Application *app);
        virtual ~CameraFunctionalityLayer();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        void processInput(GLFWwindow *window, Application *app);

        inline Camera3D *getCamera() const {return m_camera;}

        private:
        float m_moveSpeed;
        Camera3D *m_camera;
    };
}