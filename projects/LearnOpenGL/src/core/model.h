#pragma once
#include <string>
#include <vector>
#include <assimp/scene.h>
#include "texture.h"

namespace LearnOpenGL
{
    class Mesh;
    class Shader;


    struct LoadedTexture
    {
        Texture *texture;
        std::string path;
    };

    class Model
    {
        public:
        Model(const std::string &path);
        ~Model();

        void Draw(Shader *shader);


        private:
        bool m_noTextCoordsFound, m_noMaterialFound;
        std::vector<Mesh *> m_meshes;
        std::string m_directory;
        std::string m_modelName;
        std::vector<LoadedTexture *> m_textureManager;

        void processNode(aiNode *node, const aiScene *scene);
        void processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<Texture *> loadMatTextures(aiMaterial *mat, aiTextureType type);
        Texture *loadTexture(const std::string &path, TextureTypeE type);
    };
}