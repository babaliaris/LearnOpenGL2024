#pragma once
#include <glm/glm.hpp>

struct GLFWwindow;

namespace LearnOpenGL
{
    class Application;

    class Camera3D
    {
        //View space axis and origin in world space.
        struct ViewSpace
        {
            glm::vec3 m_origin; //The same as the camera position.
            glm::vec3 m_forward;
            glm::vec3 m_right;
            glm::vec3 m_up;
        };

        public:
        Camera3D(Application *app, const glm::vec3 &startPosition, const glm::vec3 &startDirection);
        ~Camera3D();

        glm::mat4 getView();

        void move(glm::vec3 direction, float speed);

        void simulateFPS();

        inline const glm::vec3 &getPosition() const {return m_coordinateSystem.m_origin;}
        inline const glm::vec3 &getForward() const {return m_coordinateSystem.m_forward;}
        inline const glm::vec3 &getRight() const {return m_coordinateSystem.m_right;}
        inline const glm::vec3 &getUp() const {return m_coordinateSystem.m_up;}

        private:
        Application *m_app;
        ViewSpace m_coordinateSystem;

        public:
        bool m_fpsSimulationStarted, m_cursorPosInitialized;
        float m_lastX, m_lastY, m_mouseSensitivity, m_yaw, m_pitch;

        public:
        void CalculateCoordinateSystem(const glm::vec3 &worldPosition, const glm::vec3 &worldDirection);
    };
}


void glfwCursorPosCallback(GLFWwindow *window, double x, double y);