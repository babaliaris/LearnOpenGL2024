#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <vamplogger/logger.h>
#include <functional>
#include "../core/application.h"
#include "../core/window.h"


namespace LearnOpenGL
{
    Camera3D::Camera3D(Application *app, const glm::vec3 &startPosition, const glm::vec3 &startDirection)
        : m_app(app), m_fpsSimulationStarted(false), m_cursorPosInitialized(false),
        m_lastX(0.0f), m_lastY(0.0f), m_mouseSensitivity(0.1f), m_yaw(-90.0f), m_pitch(0.0f)
    {
        this->CalculateCoordinateSystem(startPosition, startDirection);
    }


    Camera3D::~Camera3D()
    {

    }


    void Camera3D::CalculateCoordinateSystem(const glm::vec3 &worldPosition, const glm::vec3 &worldDirection)
    {
        //Origin (Equal to the world space camera position.)
        m_coordinateSystem.m_origin = worldPosition;

        //Forward Axis.
        m_coordinateSystem.m_forward = glm::normalize(worldDirection);

        //Right Axis.
        m_coordinateSystem.m_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), -worldDirection));

        //Up Axis.
        m_coordinateSystem.m_up = glm::normalize(glm::cross(m_coordinateSystem.m_forward, m_coordinateSystem.m_right));
    }


    glm::mat4 Camera3D::getView()
    {
        return glm::lookAt(
        m_coordinateSystem.m_origin,
        m_coordinateSystem.m_origin + m_coordinateSystem.m_forward, //The seen must move in the opposite direction of the camera.
        glm::vec3(0.0f, 1.0f, 0.0f)
        );
    }


    void Camera3D::move(glm::vec3 direction, float speed)
    {
        glm::vec3 new_position = m_coordinateSystem.m_origin + direction * speed;

        this->CalculateCoordinateSystem(new_position, m_coordinateSystem.m_forward);
    }


    void Camera3D::simulateFPS()
    {
            glfwSetInputMode(m_app->getWindow()->getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            glfwSetWindowUserPointer(m_app->getWindow()->getGlfwWindow(), this);

            glfwSetCursorPosCallback(m_app->getWindow()->getGlfwWindow(), glfwCursorPosCallback);

            m_fpsSimulationStarted = true;
    }

}


void glfwCursorPosCallback(GLFWwindow *window, double x, double y)
{
    LearnOpenGL::Camera3D *this_ = (LearnOpenGL::Camera3D *)glfwGetWindowUserPointer(window);

    if (!this_->m_cursorPosInitialized)
    {
        this_->m_lastX = (float)x;
        this_->m_lastY = (float)y;

        this_->m_cursorPosInitialized = true;
    }

    float xoffset = (float)(x - this_->m_lastX) * this_->m_mouseSensitivity;
    float yoffset = (float)(this_->m_lastY - y) * this_->m_mouseSensitivity;

    this_->m_lastX = (float)x;
    this_->m_lastY = (float)y;

    this_->m_yaw += xoffset;
    this_->m_pitch += yoffset;

    if (this_->m_pitch > 89.0f)
        this_->m_pitch = 89.0f;

    else if (this_->m_pitch < -89.0f)
        this_->m_pitch = -89.0f;

    VAMP_INFO("(%f, %f)", this_->m_yaw , this_->m_pitch);

    glm::vec3 new_camera_forward;
    new_camera_forward.x = glm::cos(glm::radians(this_->m_yaw)) * glm::cos(glm::radians(this_->m_pitch));
    new_camera_forward.y = glm::sin(glm::radians(this_->m_pitch));
    new_camera_forward.z = glm::sin(glm::radians(this_->m_yaw)) * glm::cos(glm::radians(this_->m_pitch));

    this_->CalculateCoordinateSystem(this_->getPosition(), glm::normalize(new_camera_forward));
}