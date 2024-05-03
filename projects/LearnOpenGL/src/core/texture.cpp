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
            return GL_R8;

        case 2:
            return GL_RG;

        case 3:
            return GL_RGB;

        case 4:
            return GL_RGBA;
        
        default:
            return GL_RGBA;
    }
}


LearnOpenGL::Texture::Texture(const std::string &filepath)
: m_id(0), m_filepath(filepath), m_width(0), m_height(0), m_channels(0)
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
    glCALL(glBindTexture(GL_TEXTURE_2D, 0));
}