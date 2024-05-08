#include "texture.h"
#include "../misc/stb_image.h"
#include "../debug/glcall.h"
#include <vamplogger/logger.h>
#include <glad/glad.h>


GLenum GetTextureFormat(int channels)
{
    switch (channels)
    {
        case 1:
        {
            VAMP_WARN("[Shader] 1 channel images are not supported.");
            return GL_RGB;
        }

        case 2:
            return GL_RG;

        case 3:
            return GL_RGB;

        case 4:
            return GL_RGBA;
        
        default:
        {
            VAMP_WARN("[Shader] Uknown #channels: %d", channels);
            return GL_RGBA;
        }
    }
}


LearnOpenGL::Texture::Texture(const std::string &filepath)
: m_id(0), m_filepath(filepath), m_width(0), m_height(0), m_channels(0),
m_type(TextureTypeE::NONE)
{
    glCALL(glGenTextures(1, &m_id));
    glCALL(glBindTexture(GL_TEXTURE_2D, m_id));

    glCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    glCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channels, 0);

    if (data)
    {
        glCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GetTextureFormat(m_channels), GL_UNSIGNED_BYTE, data));
        glCALL(glGenerateMipmap(GL_TEXTURE_2D));
        stbi_image_free(data);
    }

    glCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

LearnOpenGL::Texture::Texture(TextureTypeE type, int width, int height)
{
    glCALL(glGenTextures(1, &m_id));
    glCALL(glBindTexture(GL_TEXTURE_2D, m_id));

    glCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    switch (type)
    {
        case TextureTypeE::COLOR_RGB:
        {
            glCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
            break;
        }

        case TextureTypeE::COLOR_RGBA:
        {
            glCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
            break;
        }

        case TextureTypeE::DEPTH:
        {
            glCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
            break;
        }

        case TextureTypeE::STENCIL:
        {
            glCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX8, width, height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL));
            break;
        }

        case TextureTypeE::DEPTH_STENCIL:
        {
            glCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL));
            break;
        }
    
    default:
        break;
    }

    glCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

LearnOpenGL::Texture::~Texture()
{
    glCALL(glDeleteTextures(1, &m_id));
}



void LearnOpenGL::Texture::Bind(unsigned int unit)
{
    glCALL(glActiveTexture(GL_TEXTURE0 + unit));
    glCALL(glBindTexture(GL_TEXTURE_2D, m_id));
}

void LearnOpenGL::Texture::UnBind()
{   
    glCALL(glActiveTexture(GL_TEXTURE0));
    glCALL(glBindTexture(GL_TEXTURE_2D, 0));
}