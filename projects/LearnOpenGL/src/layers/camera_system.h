#pragma once
#include "../core/learnOpenGL.h"

struct GLFWwindow;

namespace LearnOpenGL
{
    class CameraSystem : public LearnOpenGL::Layer
    {
        public:
        CameraSystem(Application *app);
        virtual ~CameraSystem();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        Shader *m_shader;
        Texture *m_texture;
        unsigned int m_vao, m_vbo;
        glm::vec3 m_cubePositions[10];
        Camera3D *m_camera;
    };
}