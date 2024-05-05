#pragma once
#include "../core/learnOpenGL.h"

struct GLFWwindow;

namespace LearnOpenGL
{
    class ColorsLayer : public LearnOpenGL::Layer
    {
        public:
        ColorsLayer(Application *app);
        virtual ~ColorsLayer();

        virtual void onStart(Application *app) override;
        virtual void onUpdate(Application *app) override;

        private:
        glm::vec3 m_globalLightPos;
        Shader *m_shaderLight, *m_shaderObject;
        Texture *m_texture;
        unsigned int m_vaoLight, m_vboLight;
        unsigned int m_vaoObject, m_vboObject;
        Camera3D *m_camera;
    };
}