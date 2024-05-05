#pragma once
#include "../core/learnOpenGL.h"

struct GLFWwindow;

namespace LearnOpenGL
{
    class LightingMaps : public LearnOpenGL::Layer
    {
        public:
        LightingMaps(Application *app);
        virtual ~LightingMaps();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        Application *m_app;
        glm::vec3 m_globalLightPos;
        Shader *m_shaderLight, *m_shaderObject;
        Texture *m_diffuse, *m_specular;
        unsigned int m_vaoLight, m_vboLight;
        unsigned int m_vaoObject, m_vboObject;
        Camera3D *m_camera;


        private:
        void PrepareVertexData();
    };
}