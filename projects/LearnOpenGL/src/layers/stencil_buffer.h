#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class StencilBuffer : public LearnOpenGL::Layer
    {
        struct DirectionalLight
        {
            glm::vec3 direction;
            glm::vec3 diffuse;
            float brightness;
        };

        struct PointLight
        {
            glm::vec3 position;
            glm::vec3 diffuse;
            glm::vec3 attenuation;
            float brightness;
            float kc, kl, kq;
        };

        struct SpotLight
        {
            glm::vec3 position;
            glm::vec3 direction;
            glm::vec3 diffuse;
            glm::vec3 attenuation;
            float brightness;
            float cutoff;
            float outer;
        };

        public:
        StencilBuffer(Application *app);
        virtual ~StencilBuffer();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        Application *m_app;
        Shader *m_shader;
        Model *m_model;
        Camera3D *m_camera;
        DirectionalLight m_directionalLight;
        PointLight m_pointLight;
        SpotLight m_spotLight;

        private:
        void PrepareModel();
    };
}