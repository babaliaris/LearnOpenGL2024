#include "geometry_shader.h"
#include "cameraFunctionalityLayer.h"

namespace LearnOpenGL
{
    GeometryShader::GeometryShader(Application *app)
    : Layer("GeometryShader", app), m_vao(0), m_vbo(0), m_effect(GeometryShader::EXPLOSION),
    m_model(nullptr)
    {
    }


    GeometryShader::~GeometryShader()
    {
        delete m_shader;
        if (m_model) delete m_model;
        glCALL(glDeleteVertexArrays(1, &m_vao));
        glCALL(glDeleteBuffers(1, &m_vbo));
    }


    void GeometryShader::onStart(Application *app)
    {
        m_camera = ((CameraFunctionalityLayer *)this->findLayer("CameraFunctionalityLayer"))->getCamera();

        this->prepareData();

        std::string geometry_filepath;
        std::string vertex_filepath;
        std::string fragment_filepath;

        if (m_effect ==  GeometryShaderEffectE::EXPLOSION)
            m_model = new Model("projects/LearnOpenGL/resources/models/backpack/backpack.obj");

        switch (m_effect)
        {
            case GeometryShaderEffectE::POINTS:
                vertex_filepath     = "projects/LearnOpenGL/src/shaders/geometry_shader/vertex.glsl";
                geometry_filepath   = "projects/LearnOpenGL/src/shaders/geometry_shader/geometry_points.glsl";
                fragment_filepath   = "projects/LearnOpenGL/src/shaders/geometry_shader/fragment.glsl";
                break;

            case GeometryShaderEffectE::HOUSE:
                vertex_filepath     = "projects/LearnOpenGL/src/shaders/geometry_shader/vertex.glsl";
                geometry_filepath = "projects/LearnOpenGL/src/shaders/geometry_shader/geometry_house.glsl";
                fragment_filepath   = "projects/LearnOpenGL/src/shaders/geometry_shader/fragment.glsl";
                break;

            case GeometryShaderEffectE::EXPLOSION:
                vertex_filepath     = "projects/LearnOpenGL/src/shaders/phong_vertex.glsl";
                geometry_filepath   = "projects/LearnOpenGL/src/shaders/geometry_shader/geometry_points.glsl";
                fragment_filepath   = "projects/LearnOpenGL/src/shaders/phong_fragment.glsl";
                break;
            
            default:
                vertex_filepath     = "projects/LearnOpenGL/src/shaders/geometry_shader/vertex.glsl";
                geometry_filepath = "projects/LearnOpenGL/src/shaders/geometry_shader/geometry_points.glsl";
                fragment_filepath   = "projects/LearnOpenGL/src/shaders/geometry_shader/fragment.glsl";
                break;
        }

        m_shader = new Shader(
            vertex_filepath,
            geometry_filepath,
            fragment_filepath);
    }


    void GeometryShader::onUpdate(Application *app)
    {
        if (m_effect != GeometryShaderEffectE::EXPLOSION)
        {
            glCALL(glBindVertexArray(m_vao));
            m_shader->Bind();
            glCALL(glDrawArrays(GL_POINTS, 0, 4));
        }

        else
        {
            m_shader->SetUniform("u_model", glm::mat4(1.0f));
            m_shader->SetUniform("u_view", m_camera->getView());
            m_shader->SetUniform("u_proj", glm::perspective(glm::radians(45.0f), (float)app->getWindow()->getWidth() / app->getWindow()->getHeight(), 0.1f, 100.0f));
            m_shader->SetUniform("u_normal", glm::mat4(1.0f));

            m_shader->SetUniform("u_enableObjectOutline", 0);

            m_shader->SetUniform("u_ambientFactor", 1.0f);
            m_shader->SetUniform("u_numberOfDirectionalLights", 0);
            m_shader->SetUniform("u_numberOfPointLights", 0);
            m_shader->SetUniform("u_numberOfSpotLights", 0);
            m_model->Draw(m_shader);
        }
    }


    void GeometryShader::prepareData()
    {
        float points[] = {
            -0.5f,  0.5f, // top-left
             0.5f,  0.5f, // top-right
             0.5f, -0.5f, // bottom-right
            -0.5f, -0.5f  // bottom-left
        }; 

        glCALL(glGenVertexArrays(1, &m_vao));
        glCALL(glBindVertexArray(m_vao));

        glCALL(glGenBuffers(1, &m_vbo));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
        glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW));

        glCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0));
        glCALL(glEnableVertexAttribArray(0));

        glCALL(glBindVertexArray(0));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}