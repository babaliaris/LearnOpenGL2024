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
        delete m_diffuse;
        delete m_specular;
        delete m_shader;
        delete m_mesh;
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
        
        m_mesh->Draw(m_shader);
    }


    void TestModelLoading::PrepareMesh()
    {   
        //Vertices.
        std::vector<Vertex> vertices = {
                //Positions                         Normals                     Texture Coordinates
            {glm::vec3(-0.5f, -0.5f, 0.0f),     glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
            {glm::vec3(0.5f, -0.5f, 0.0f),      glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
            {glm::vec3(0.5f, 0.5f, 0.0f),       glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
            {glm::vec3(-0.5f,   0.5f,  0.0f),   glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}
        };

        //Indicies
        std::vector<unsigned int> indicies = {
            0, 1, 2, //Down Triangle
            0, 2, 3  //Up Triangle
        };

        m_diffuse = new Texture("projects/LearnOpenGL/resources/diffuse_container.png");
        m_diffuse->setType(TextureTypeE::DIFFUSE);

        m_specular = new Texture("projects/LearnOpenGL/resources/specular_container.png");
        m_specular->setType(TextureTypeE::SPECULAR);

        m_shader = new Shader("projects/LearnOpenGL/src/shaders/test_model_loading_vertex.glsl",
        "projects/LearnOpenGL/src/shaders/test_model_loading_fragment.glsl");

        m_shader->SetUniform("u_model", glm::mat4(1.0f));
        //m_shader->SetUniform("u_normalMat", glm::mat3(1.0f));

        std::vector<Texture *> textures = {
            m_diffuse,
            m_specular
        };

        m_mesh = new Mesh(vertices, indicies, textures);
    }
}