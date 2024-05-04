#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class CameraLayer : public LearnOpenGL::Layer
    {
        public:
        CameraLayer();
        virtual ~CameraLayer();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        Shader *m_shader;
        Texture *m_texture;
        unsigned int m_vao, m_vbo;
        glm::vec3 m_cubePositions[10];
        glm::mat4 m_view;
        float m_rotationSpeed = 50.0f;
    };
}