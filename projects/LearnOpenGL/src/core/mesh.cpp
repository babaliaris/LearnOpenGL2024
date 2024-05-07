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
    Mesh::Mesh(void *vertices, signed long int verticiesSize,
        void *indices, unsigned int indiciesCount, const std::vector<Texture *> &textures)
    : m_vao(0), m_vbo(0), m_ebo(0), m_indicesCount(indiciesCount)
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
        glCALL(glBufferData(GL_ARRAY_BUFFER, verticiesSize, vertices, GL_STATIC_DRAW));


        //EBO
        glCALL(glGenBuffers(1, &m_ebo));
        glCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
        glCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indiciesCount, indices, GL_STATIC_DRAW));

        //Positions.
        glCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)0));
        glCALL(glEnableVertexAttribArray(0));

        //Normals.
        glCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(sizeof(float) * 3)));
        glCALL(glEnableVertexAttribArray(1));

        //Texture Coordinates.
        glCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(sizeof(float) * 6)));
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
        
        shader->Bind();
        glCALL(glBindVertexArray(m_vao));
        glCALL(glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0));
        glCALL(glBindVertexArray(0));

        for (Texture *texture : m_textures)
            texture->UnBind();
    }
}