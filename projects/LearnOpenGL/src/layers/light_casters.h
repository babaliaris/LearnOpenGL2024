#pragma once
#include "../core/learnOpenGL.h"

struct GLFWwindow;

namespace LearnOpenGL
{
    class LightingCasters : public LearnOpenGL::Layer
    {
        struct DirectionalLight
        {
            glm::vec3 direction;
            glm::vec3 diffuse;
            float brightness;
        };

        public:
        LightingCasters(Application *app);
        virtual ~LightingCasters();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        Application *m_app;
        DirectionalLight m_directionalLight;
        Shader *m_shaderObject;
        Texture *m_diffuse, *m_specular;
        unsigned int m_vaoObject, m_vboObject;
        Camera3D *m_camera;
        glm::vec3 m_cubePositions[10];


        private:
        void PrepareVertexData();
        void ProcessInput();
    };
}