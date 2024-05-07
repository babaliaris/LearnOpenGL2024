#include "model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <sstream>
#include <vamplogger/logger.h>
#include "shader.h"
#include "mesh.h"


namespace LearnOpenGL
{
    Model::Model(const std::string &path)
    : m_noTextCoordsFound(false), m_noMaterialFound(false)
    {
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            VAMP_ERROR("[Assimp Import Error] %s", importer.GetErrorString());
            return;
        }

        m_directory = path.substr(0, path.find_last_of("/"));

        m_modelName = path.substr(path.find_last_of("/"), path.size());

        this->processNode(scene->mRootNode, scene);

        if (m_noTextCoordsFound)
        {
            VAMP_WARN("[Assimp] No texture coordinates found for model: %s. ", m_modelName.c_str());
        }

        if (m_noMaterialFound)
        {
            VAMP_WARN("[Assimp] No material found for model: %s. ", m_modelName.c_str());
        }
    }

    Model::~Model()
    {
        //Delete all the textures.
        for (LoadedTexture *loadedTexture : m_textureManager)
        {
            delete loadedTexture->texture;
            delete loadedTexture;
        }

        //Delete all the meshes.
        for (Mesh *mesh : m_meshes)
        {
            delete mesh;
        }
    }


    void Model::Draw(Shader *shader)
    {
        //Draw all the meshes.
        for (Mesh *mesh : m_meshes)
        {
            mesh->Draw(shader);
        }
    }


    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            this->processMesh(scene->mMeshes[node->mMeshes[i]], scene);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            this->processNode(node->mChildren[i], scene);
        }
    }


    void Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indicies;
        std::vector<Texture *> textures;

        //Get Vertices.
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec2 texCoord;

            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;

            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;

            if (mesh->mTextureCoords[0])
            {
                texCoord.x = mesh->mTextureCoords[0][i].x;
                texCoord.y = mesh->mTextureCoords[0][i].y;
            }

            else
            {
                texCoord.x = 0.0f;
                texCoord.y = 0.0f;
                m_noTextCoordsFound = true;
            }

            vertices.push_back({position, normal, texCoord});
        }


        //Get Indicies.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indicies.push_back( face.mIndices[j] );
            }
        }

        //Get the Material.
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<Texture *> diffuse_textures = this->loadMatTextures(mat, aiTextureType_DIFFUSE);
            std::vector<Texture *> specular_textures = this->loadMatTextures(mat, aiTextureType_SPECULAR);

            textures.insert(textures.end(), diffuse_textures.begin(), diffuse_textures.end());
            textures.insert(textures.end(), specular_textures.begin(), specular_textures.end());
        }

        else
        {
            m_noMaterialFound = true;
        }

        m_meshes.push_back(new Mesh(vertices, indicies, textures));
    }


    std::vector<Texture *> Model::loadMatTextures(aiMaterial *mat, aiTextureType type)
    {
        std::vector<Texture *> textures;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            std::stringstream full_path;

            aiString str;

            mat->GetTexture(type, i, &str);

            TextureTypeE texType    = type == aiTextureType::aiTextureType_DIFFUSE ? TextureTypeE::DIFFUSE : TextureTypeE::NONE;
            texType                 = type == aiTextureType::aiTextureType_SPECULAR ? TextureTypeE::SPECULAR : TextureTypeE::NONE;

            full_path << m_directory << "/" << str.C_Str();

            Texture *texture = this->loadTexture(full_path.str(), texType);

            textures.push_back(texture);
        }

        return textures;
    }


    Texture *Model::loadTexture(const std::string &path, TextureTypeE type)
    {
        //Check if texture has been already loaded.
        for (LoadedTexture *loadedTexture : m_textureManager)
        {
            if (loadedTexture->path == path)
            {
                return loadedTexture->texture;
            }
        }

        //Create new texture.
        Texture *texture = new Texture(path);
        texture->setType(type);

        //Append it to the texture manager.
        LoadedTexture *new_loaded_texture = new LoadedTexture();
        new_loaded_texture->path = path;
        new_loaded_texture->texture = texture;
        m_textureManager.push_back(new_loaded_texture);

        return texture;
    }
}