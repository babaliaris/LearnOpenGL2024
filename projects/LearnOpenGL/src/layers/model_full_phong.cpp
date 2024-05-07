#include "model_full_phong.h"
#include "cameraFunctionalityLayer.h"

namespace LearnOpenGL
{
    ModelFullPhong::ModelFullPhong(Application *app)
    : Layer("ModelFullPhong", app), m_app(app), m_model(nullptr)
    {
        m_directionalLight.direction    = glm::vec3(0.0f, -4.0f, -1.0f);
        m_directionalLight.diffuse      = glm::vec3(1.0f, 1.0f, 1.0f);
        m_directionalLight.brightness   = 1.0f;

        
        m_pointLight.position   = glm::vec3(0.0f, 2.0f, 4.0f);
        m_pointLight.diffuse    = glm::vec3(1.0f, 1.0f, 1.0f);
        m_pointLight.brightness = 1.0f;
        m_pointLight.attenuation= glm::vec3(1.0f, 0.09f, 0.032f);

        /*
        m_spotLight.diffuse     = glm::vec3(1.0f, 1.0f, 1.0f);
        m_spotLight.brightness  = 1.0f;
        m_spotLight.attenuation = glm::vec3(1.0f, 0.09f, 0.032f);
        m_spotLight.cutoff      = glm::cos(glm::radians(12.0f));
        m_spotLight.outer       = glm::cos(glm::radians(15.0f));
        */
    }


    ModelFullPhong::~ModelFullPhong()
    {
        delete m_model;
        delete m_shader;

    }


    void ModelFullPhong::onStart(Application *app)
    {
        m_camera = ((CameraFunctionalityLayer *)this->findLayer("CameraFunctionalityLayer"))->getCamera();

        this->PrepareMesh();
    }


    void ModelFullPhong::onUpdate(Application *app)
    {
        m_shader->SetUniform("u_proj", glm::perspective(glm::radians(45.0f), 
        app->getWindow()->getWidth() / (float)app->getWindow()->getHeight(), 0.1f, 100.0f));

        m_shader->SetUniform("u_view", m_camera->getView());

        m_shader->SetUniform("u_CamPos", m_camera->getPosition());
        
        if (m_model)
            m_model->Draw(m_shader);
    }


    void ModelFullPhong::PrepareMesh()
    {
        m_shader = new Shader("projects/LearnOpenGL/src/shaders/phong_vertex.glsl",
        "projects/LearnOpenGL/src/shaders/phong_fragment.glsl");

        glm::mat4 model     = glm::mat4(1.0f);
        glm::mat4 normal    = glm::mat4(1.0f);
        model               = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
        normal              = glm::transpose(glm::inverse(model));

        m_shader->SetUniform("u_model", model);
        m_shader->SetUniform("u_normal", normal);

        m_shader->SetUniform("u_ambientFactor", 0.1f);
        m_shader->SetUniform("u_numberOfDirectionalLights", 1);
        m_shader->SetUniform("u_numberOfPointLights", 1);
        m_shader->SetUniform("u_numberOfSpotLight", 0);

        //Directional Light Properties.
        m_shader->SetUniform("u_directionalLight.direction", m_directionalLight.direction);
        m_shader->SetUniform("u_directionalLight.diffuse", m_directionalLight.diffuse);
        m_shader->SetUniform("u_directionalLight.brightness", m_directionalLight.brightness);

        
        //Point Light Properties.
        m_shader->SetUniform("u_pointLight.position", m_pointLight.position);
        m_shader->SetUniform("u_pointLight.diffuse", m_pointLight.diffuse);
        m_shader->SetUniform("u_pointLight.brightness", m_pointLight.brightness);
        m_shader->SetUniform("u_pointLight.attenuation", m_pointLight.attenuation);

        /*
        //Spot Light Properties.
        m_shader->SetUniform("u_spotLight.diffuse", m_spotLight.diffuse);
        m_shader->SetUniform("u_spotLight.brightness", m_spotLight.brightness);
        m_shader->SetUniform("u_spotLight.attenuation", m_spotLight.attenuation);
        m_shader->SetUniform("u_spotLight.cutoff", m_spotLight.cutoff);
        m_shader->SetUniform("u_spotLight.outer", m_spotLight.outer);
        */

        m_model = new Model("projects/LearnOpenGL/resources/models/backpack/backpack.obj");
    }
}