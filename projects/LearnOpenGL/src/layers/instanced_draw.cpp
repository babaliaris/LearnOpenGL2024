#include "instanced_draw.h"
#include "cameraFunctionalityLayer.h"

namespace LearnOpenGL
{
    InstancedDraw::InstancedDraw(Application *app)
    : Layer("InstancedDraw", app), m_vao(0), m_vbo(0), 
    m_effect(InstancedDraw::QUADS), m_model(nullptr),
    m_instancedVBO(0)
    {
    }


    InstancedDraw::~InstancedDraw()
    {
        delete m_shader;
        if (m_model) delete m_model;
        glCALL(glDeleteVertexArrays(1, &m_vao));
        glCALL(glDeleteBuffers(1, &m_vbo));
    }


    void InstancedDraw::onStart(Application *app)
    {
        m_camera = ((CameraFunctionalityLayer *)this->findLayer("CameraFunctionalityLayer"))->getCamera();

        this->prepareData();

        std::string vertex_filepath;
        std::string fragment_filepath;

        if (m_effect ==  InstancedDraw::ASTEROID)
            m_model = new Model("projects/LearnOpenGL/resources/models/backpack/backpack.obj");

        switch (m_effect)
        {
            case InstancedDraw::QUADS:
                vertex_filepath     = "projects/LearnOpenGL/src/shaders/instanced_rendering/instanced_vertex.glsl";
                fragment_filepath   = "projects/LearnOpenGL/src/shaders/instanced_rendering/instanced_fragment.glsl";
                break;
            
            default:
                vertex_filepath     = "projects/LearnOpenGL/src/shaders/geometry_shader/vertex.glsl";
                fragment_filepath   = "projects/LearnOpenGL/src/shaders/geometry_shader/fragment.glsl";
                break;
        }

        m_shader = new Shader(
            vertex_filepath,
            fragment_filepath);
    }


    void InstancedDraw::onUpdate(Application *app)
    {
        if (m_effect == InstancedDrawE::QUADS)
        {
            glCALL(glBindVertexArray(m_vao));
            m_shader->Bind();
            glCALL(glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100));
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

            m_shader->SetUniform("u_time", (float)glm::radians(glfwGetTime()));

            m_model->Draw(m_shader);
        }
    }


    void InstancedDraw::prepareData()
    {
        //Counter Clocked Wise Vertices.
        float vertices[] = {
            // positions     // colors
            -0.05f, -0.05f,  1.0f, 0.0f, 0.0f,  //Bottom Right
             0.05f, -0.05f,  0.0f, 1.0f, 0.0f,  //Bottom Left
             0.05f,  0.05f,  0.0f, 0.0f, 1.0f,  //Top Right

            -0.05f, -0.05f,  1.0f, 0.0f, 0.0f,  //Bottom Right
             0.05f,  0.05f,  0.0f, 0.0f, 1.0f,  //Top Right
            -0.05f,  0.05f,  0.0f, 1.0f, 1.0f   //Top Left.
        };

        //Create the NDC Offsets for each vertex position (x,y).
        glm::vec2   translations[100];
        int         index = 0;
        float       offset = 0.1f;
        for(int y = -10; y < 10; y += 2)
        {
            for(int x = -10; x < 10; x += 2)
            {
                glm::vec2 translation;
                translation.x = (float)x / 10.0f + offset;
                translation.y = (float)y / 10.0f + offset;
                translations[index++] = translation;
            }
        }  


        //VAO
        glCALL(glGenVertexArrays(1, &m_vao));
        glCALL(glBindVertexArray(m_vao));
        
        //Positions and Colors in one VBO.
        glCALL(glGenBuffers(1, &m_vbo));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
        glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        //Positions
        glCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0));
        glCALL(glEnableVertexAttribArray(0));

        //Colors.
        glCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)(sizeof(float)*2)));
        glCALL(glEnableVertexAttribArray(1));

        //Instanced Translations VBO.
        glCALL(glGenBuffers(1, &m_instancedVBO));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_instancedVBO));
        glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW));

        //Traslations.
        glCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *)0)); //This will be applied to the current binded VBO and VAO.
        glCALL(glEnableVertexAttribArray(2));
        glCALL(glVertexAttribDivisor(2, 1)); //Make Translations (attribute 2) update in the vertex shader for each instance!

        //Unbind Everything.
        glCALL(glBindVertexArray(0));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}