#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class InstancedDraw : public LearnOpenGL::Layer
    {
        enum InstancedDrawE
        {
            QUADS,
            ASTEROID
        };


        public:
        InstancedDraw(Application *app);
        virtual ~InstancedDraw();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        
        unsigned int m_vao, m_vbo, m_instancedVBO;
        Shader *m_shader;
        InstancedDrawE m_effect;
        Model *m_model;
        Camera3D *m_camera;

        void prepareData();
    };
}