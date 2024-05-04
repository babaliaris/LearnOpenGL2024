#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class More3D : public LearnOpenGL::Layer
    {
        public:
        More3D();
        virtual ~More3D();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        Shader *m_shader;
        Texture *m_texture;
        unsigned int m_vao, m_vbo;
        glm::mat4 m_model;
    };
}