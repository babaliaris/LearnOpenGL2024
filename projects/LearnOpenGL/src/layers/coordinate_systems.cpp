#include "coordinate_systems.h"



namespace LearnOpenGL
{

    CoordinateSystems::CoordinateSystems()
    : Layer("CoordinateSystems"), m_shader(nullptr), m_texture(nullptr), m_vao(0), m_vbo(0)
    {
    }


    CoordinateSystems::~CoordinateSystems()
    {
        delete m_shader;
        delete m_texture;
    }


    void CoordinateSystems::onStart(Application *app)
    {
        float vertices[] = {
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
                0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
                0.0f, 0.5f, 0.0f,   0.5f, 1.0f,
            };

            glCALL(glGenVertexArrays(1, &m_vao));
            glCALL(glBindVertexArray(m_vao));

            glCALL(glGenBuffers(1, &m_vbo));
            glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
            glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

            glCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void *)0));
            glCALL(glEnableVertexAttribArray(0));

            glCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void *) (sizeof(float) * 3) ));
            glCALL(glEnableVertexAttribArray(1));

            glCALL(glBindVertexArray(0));
            glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

            std::stringstream vertexPath, fragmentPath;
            vertexPath << "projects/LearnOpenGL/src/shaders/mvp_vertex.glsl";
            fragmentPath << "projects/LearnOpenGL/src/shaders/texture_fragment.glsl";

            m_shader = new LearnOpenGL::Shader(vertexPath.str().c_str(), fragmentPath.str().c_str());
            m_shader->SetUniform("m_texture", 0);

            m_texture = new LearnOpenGL::Texture("projects/LearnOpenGL/resources/wall.jpg");


            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view  = glm::mat4(1.0f);
            glm::mat4 proj  = glm::mat4(1.0f);

            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

            proj = glm::perspective(
                glm::radians(45.0f),
                (float)app->getWindow()->getWidth() / app->getWindow()->getHeight(),
                0.1f,
                100.0f);

            m_shader->SetUniform("model", model);
            m_shader->SetUniform("view", view);
            m_shader->SetUniform("proj", proj);
    }


    void CoordinateSystems::onUpdate(Application *app)
    {
        glCALL(glBindVertexArray(m_vao));
        m_shader->Bind();
        m_texture->Bind();
        glCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
        glCALL(glBindVertexArray(0));
        m_shader->Unbind();
        m_texture->UnBind();
    }

}