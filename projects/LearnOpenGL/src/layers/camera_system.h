#pragma once
#include "../core/learnOpenGL.h"

struct GLFWwindow;

namespace LearnOpenGL
{
    class CameraSystem : public LearnOpenGL::Layer
    {
        public:
        CameraSystem();
        virtual ~CameraSystem();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        void processInput(GLFWwindow *window, Application *app);

        private:
        Shader *m_shader;
        Texture *m_texture;
        unsigned int m_vao, m_vbo;
        glm::vec3 m_cubePositions[10];
        float m_moveSpeed;
        Camera3D *m_camera;
    };
}