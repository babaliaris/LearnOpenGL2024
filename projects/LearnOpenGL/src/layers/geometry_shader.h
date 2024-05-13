#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class GeometryShader : public LearnOpenGL::Layer
    {
        enum GeometryShaderEffectE
        {
            POINTS,
            HOUSE,
            EXPLOSION
        };


        public:
        GeometryShader(Application *app);
        virtual ~GeometryShader();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        
        unsigned int m_vao, m_vbo;
        Shader *m_shader;
        GeometryShaderEffectE m_effect;
        Model *m_model;
        Camera3D *m_camera;

        void prepareData();
    };
}