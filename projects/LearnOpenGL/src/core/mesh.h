#pragma once
#include <glm/glm.hpp>
#include <vector>

#define MAX_NUMBER_OF_DIFFUSE_TEXTURES 4
#define MAX_NUMBER_OF_SPECULAR_TEXTURES 4

namespace LearnOpenGL
{
    class Texture;
    class Shader;

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoordinate;
    };

    class Mesh
    {
        public:
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indicies, const std::vector<Texture *> &textures);

        ~Mesh();

        void Draw(Shader *shader);


        private:
        unsigned int m_vao, m_vbo, m_ebo;
        int m_indicesCount;
        std::vector<Texture *> m_textures;
    };
}