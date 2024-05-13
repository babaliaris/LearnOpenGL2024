#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class GeometryShader : public LearnOpenGL::Layer
    {
        public:
        GeometryShader(Application *app);
        virtual ~GeometryShader();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        unsigned int m_vao, m_vbo;
    };
}