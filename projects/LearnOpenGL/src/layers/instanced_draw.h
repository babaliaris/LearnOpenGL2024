#pragma once
#include "../core/learnOpenGL.h"

#define ASTEROID_AMOUNT 10000

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
        Model *m_planetModel, *m_asteroidModel;
        Camera3D *m_camera;
        glm::mat4 m_modelMatrices[ASTEROID_AMOUNT];

        void prepareData();
        void prepareInstanceModels();
    };
}