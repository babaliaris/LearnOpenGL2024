#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class Antializing : public LearnOpenGL::Layer
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
        Antializing(Application *app);
        virtual ~Antializing();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        unsigned int m_vaoCube, m_vboCube;
        unsigned int m_vaoSkybox, m_vboSkybox;
        Application *m_app;
        Shader *m_shader, *m_shaderSkybox, *m_shaderReflectRefract;
        Camera3D *m_camera;
        DirectionalLight m_directionalLight;
        PointLight m_pointLight;
        SpotLight m_spotLight;
        Texture *m_cubeDiffuse, *m_cubeSpecular;
        std::vector<glm::vec3> m_cubePositions;
        CubeMap *m_skyBox;

        private:
        void PrepareCubeData();
        void PrepareSkyboxData();
        void RenderCube();
        void RenderSkybox();
        void RenderReflectRefractCube(const glm::mat4 model, const glm::mat4 &proj, int mode);
    };
}