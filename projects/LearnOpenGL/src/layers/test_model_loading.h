#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class TestModelLoading : public LearnOpenGL::Layer
    {
        public:
        TestModelLoading(Application *app);
        virtual ~TestModelLoading();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        Application *m_app;
        Shader *m_shader;
        Texture *m_diffuse, *m_specular;
        Mesh *m_mesh;
        Camera3D *m_camera;

        private:
        void PrepareMesh();
    };
}