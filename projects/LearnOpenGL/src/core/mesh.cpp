#include "mesh.h"
#include <string>
#include <sstream>
#include <vamplogger/logger.h>
#include <glad/glad.h>
#include "../debug/glcall.h"
#include "texture.h"
#include "shader.h"


namespace LearnOpenGL
{
    Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indicies, const std::vector<Texture *> &textures)
    : m_vao(0), m_vbo(0), m_ebo(0), m_instancedCount(0), m_indicesCount(indicies.size()), m_instancedDraw(false)
    {
        //Set up the textures.
        int max_textures = MAX_NUMBER_OF_DIFFUSE_TEXTURES + MAX_NUMBER_OF_SPECULAR_TEXTURES;
        if (m_textures.size() > max_textures)
        {
            VAMP_WARN("[Mesh Constructor] The maximum number of textures are %d but you gave %d.", max_textures, textures.size())
        }
        m_textures = textures;

        //Vao
        glCALL(glGenVertexArrays(1, &m_vao));
        glCALL(glBindVertexArray(m_vao));

        //VBO
        glCALL(glGenBuffers(1, &m_vbo));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
        glCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW));


        //EBO
        glCALL(glGenBuffers(1, &m_ebo));
        glCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
        glCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indicesCount, &indicies[0], GL_STATIC_DRAW));

        //Positions.
        glCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0));
        glCALL(glEnableVertexAttribArray(0));

        //Normals.
        glCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal)));
        glCALL(glEnableVertexAttribArray(1));

        //Texture Coordinates.
        glCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoordinate)));
        glCALL(glEnableVertexAttribArray(2));


        glCALL(glBindVertexArray(0));
        glCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    Mesh::~Mesh()
    {
        glCALL(glDeleteVertexArrays(1, &m_vao));
        glCALL(glDeleteBuffers(1, &m_vbo));
        glCALL(glDeleteBuffers(1, &m_ebo));
    }

    void Mesh::Draw(Shader *shader)
    {
        int diffuse_number = 0;
        int specular_number = 0;

        //Set the texture material uniforms.
        for (int i = 0; i < m_textures.size(); i++)
        {
            std::stringstream ss;
            ss << "u_material.";

            //Diffuse.
            if (m_textures[i]->getType() == TextureTypeE::DIFFUSE)
            {
                ss << "diffuse" << diffuse_number;
                shader->SetUniform(ss.str().c_str(), diffuse_number);
                diffuse_number++;
            }

            //Specular.
            else if (m_textures[i]->getType() == TextureTypeE::SPECULAR)
            {
                ss << "specular" << specular_number;
                shader->SetUniform(ss.str().c_str(), specular_number);
                specular_number++;
            }

            else
            {
                VAMP_WARN("[Mesh::Draw()] This type of material does not exist.");
            }

            m_textures[i]->Bind(i);
        }

        shader->SetUniform("u_material.numOfDiffuse", diffuse_number);
        shader->SetUniform("u_material.numOfSpecular", specular_number);
        shader->SetUniform("u_instancedDraw", m_instancedDraw ? 1 : 0);
        
        //Bind the shader and the VAO.
        shader->Bind();
        glCALL(glBindVertexArray(m_vao));

        //Instanced Draw Call.
        if (m_instancedDraw)
        {
            glDrawElementsInstanced(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0, m_instancedCount);
        }

        //Regular Draw Call.
        else
        {
            glCALL(glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0));
        }

        //Unbind Everything.
        glCALL(glBindVertexArray(0));
        for (Texture *texture : m_textures)
            texture->UnBind();
    }



    void Mesh::setInstancedDrawCall(unsigned int count, unsigned int modelsVBO)
    {
        //Enable the flag.
        this->m_instancedDraw  = true;
        this->m_instancedCount = count;

        //Bind the VAO.
        glCALL(glBindVertexArray(m_vao));

        //Bind the models VBO.
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, modelsVBO));

        //--------------------------------Store each column in a different attribute--------------------------------//
        //THE STRIDE MUST BE EQUAL TO THE SIZE OF THE MATRIX sizeof(glm::vec4) * 4 = 16 * 4 = 64 BYTES!!!

        //Column 1
        glCALL(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (void *)0));
        glCALL(glEnableVertexAttribArray(3));

        //Column 2
        glCALL(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (void *)(sizeof(glm::vec4) * 1))); // 4 * 1 = 4
        glCALL(glEnableVertexAttribArray(4));

        //Column 3
        glCALL(glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (void *)(sizeof(glm::vec4) * 2))); // 4 * 2 = 8
        glCALL(glEnableVertexAttribArray(5));

        //Column 4
        glCALL(glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (void *)(sizeof(glm::vec4) * 3))); // 4 * 3 = 12
        glCALL(glEnableVertexAttribArray(6));

        //--------------------------------Store each column in a different attribute--------------------------------//

        //Enable instance reading.
        glCALL(glVertexAttribDivisor(3, 1));
        glCALL(glVertexAttribDivisor(4, 1));
        glCALL(glVertexAttribDivisor(5, 1));
        glCALL(glVertexAttribDivisor(6, 1));

        //Unbind the buffers.
        glCALL(glBindVertexArray(0));
        glCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}