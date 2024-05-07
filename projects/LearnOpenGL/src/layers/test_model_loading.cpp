#include "test_model_loading.h"
#include "cameraFunctionalityLayer.h"

namespace LearnOpenGL
{
    TestModelLoading::TestModelLoading(Application *app)
    : Layer("TestModelLoading", app), m_app(app)
    {

    }


    TestModelLoading::~TestModelLoading()
    {
        delete m_model;
        delete m_shader;

    }


    void TestModelLoading::onStart(Application *app)
    {
        m_camera = ((CameraFunctionalityLayer *)this->findLayer("CameraFunctionalityLayer"))->getCamera();

        this->PrepareMesh();
    }


    void TestModelLoading::onUpdate(Application *app)
    {
        m_shader->SetUniform("u_proj", glm::perspective(glm::radians(45.0f), 
        app->getWindow()->getWidth() / (float)app->getWindow()->getHeight(), 0.1f, 100.0f));

        m_shader->SetUniform("u_view", m_camera->getView());
        
        m_model->Draw(m_shader);
    }


    void TestModelLoading::PrepareMesh()
    {   
        /*
        //Vertices.
        float vertices[] = {
            //Positions                      Normals          Texture Coordinates
            -0.5f,  -0.5f,  0.0f,       0.0f, 0.0f, 1.0f,       0.0f, 0.0f, //0: Bottom Left
             0.5f,  -0.5f,  0.0f,       0.0f, 0.0f, 1.0f,       1.0f, 0.0f, //1: Bottom Right
             0.5f,   0.5f,  0.0f,       0.0f, 0.0f, 1.0f,       1.0f, 1.0f, //2: Top Right
            -0.5f,   0.5f,  0.0f,       0.0f, 0.0f, 1.0f,       0.0f, 1.0f  //3: Top Left
        };

        //Indicies
        unsigned int indicies[6] = {
            0, 1, 2, //Down Triangle
            0, 2, 3  //Up Triangle
        };
        */

       /*
       std::vector<Vertex> verticies = {
            //         Positions                        Normals                Texture Coordinates
            { glm::vec3(-0.5f,  -0.5f,  0.0f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f) }, //0: Bottom Left
            {  glm::vec3(0.5f,  -0.5f,  0.0f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f) }, //1: Bottom Right
            {  glm::vec3(0.5f,   0.5f,  0.0f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f) }, //2: Top Right
            { glm::vec3(-0.5f,   0.5f,  0.0f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f) }  //3: Top Left
       };

       std::vector<unsigned int> indicies = {
            0, 1, 2, //Down Triangle
            0, 2, 3  //Up Triangle
       };
       */

        m_shader = new Shader("projects/LearnOpenGL/src/shaders/test_model_loading_vertex.glsl",
        "projects/LearnOpenGL/src/shaders/test_model_loading_fragment.glsl");

        glm::mat4 model     = glm::mat4(1.0f);
        glm::mat4 normal    = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
        normal = glm::transpose(glm::inverse(model));

        m_shader->SetUniform("u_model", model);
        m_shader->SetUniform("u_normal", normal);

        m_model = new Model("projects/LearnOpenGL/resources/models/backpack/backpack.obj");
    }
}