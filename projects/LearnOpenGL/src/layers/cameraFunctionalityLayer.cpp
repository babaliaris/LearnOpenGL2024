#include "cameraFunctionalityLayer.h"


namespace LearnOpenGL
{

    CameraFunctionalityLayer::CameraFunctionalityLayer(Application *app)
    : Layer("CameraFunctionalityLayer", app), m_moveSpeed(10.0f), m_sprintSpeed(50.0f), m_actualSpeed(0.0f)
    {
        m_actualSpeed = m_moveSpeed;
    }


    CameraFunctionalityLayer::~CameraFunctionalityLayer()
    {
        delete m_camera;
    }


    void CameraFunctionalityLayer::onStart(Application *app)
    {
        m_camera = new Camera3D(app, glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        m_camera->simulateFPS();
    }


    void CameraFunctionalityLayer::onUpdate(Application *app)
    {
        this->processInput(app->getWindow()->getGlfwWindow(), app);
    }


    void CameraFunctionalityLayer::processInput(GLFWwindow *window, Application *app)
    {
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            m_camera->move( m_camera->getForward(), m_actualSpeed * app->getDeltaTime());
        }


        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            m_camera->move( -m_camera->getForward(), m_actualSpeed * app->getDeltaTime());
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            m_camera->move( -m_camera->getRight(), m_actualSpeed * app->getDeltaTime());
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_camera->move( m_camera->getRight(), m_actualSpeed * app->getDeltaTime());
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            m_actualSpeed = m_sprintSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            m_actualSpeed = m_moveSpeed;
        }
    }

}