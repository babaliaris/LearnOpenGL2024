#pragma once
#include "../core/learnOpenGL.h"


namespace LearnOpenGL
{
    class Skybox : public LearnOpenGL::Layer
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
        Skybox(Application *app);
        virtual ~Skybox();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        unsigned int m_vaoCube, m_vboCube;
        unsigned int m_vaoPlane, m_vboPlane;
        unsigned int m_vaoPostProcess, m_vboPostProcess;
        Application *m_app;
        Shader *m_shader, *m_postProcessShader;
        Camera3D *m_camera;
        DirectionalLight m_directionalLight;
        PointLight m_pointLight;
        SpotLight m_spotLight;
        Texture *m_cubeDiffuse, *m_cubeSpecular;
        Texture *m_windowTexture, *m_grassTexture;
        std::vector<glm::vec3> m_cubePositions;
        std::vector<glm::vec3> m_grassPositions;
        std::vector<glm::vec3> m_windowPositions;

        private:
        void PrepareCubeData();
        void PreparePlaneData();
        void RenderCube();
        void RenderPlane(bool isGrass);
    };
}