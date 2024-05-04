#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class CoordinateSystems : public LearnOpenGL::Layer
    {
        public:
        CoordinateSystems();
        virtual ~CoordinateSystems();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        Shader *m_shader;
        Texture *m_texture;
        unsigned int m_vao, m_vbo;
    };
}