#include "cubemap.h"
#include "../misc/stb_image.h"
#include "../debug/glcall.h"
#include <vamplogger/logger.h>
#include <glad/glad.h>


static GLenum GetTextureFormat(int channels)
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


LearnOpenGL::CubeMap::CubeMap(const std::vector<std::string> &paths)
: m_id(0), m_filepaths(paths), m_width(0), m_height(0), m_channels(0)
{
    if (paths.size() != 6)
    {
        VAMP_ERROR("[CubeMap] A cube map must have exactly 6 textures!");
        return;
    }

    glCALL(glGenTextures(1, &m_id));
    glCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_id));

    glCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    glCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    glCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    int width, height, channels;
    
    for (unsigned int i = 0; i < paths.size(); i++)
    {

        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(paths[i].c_str(), &m_width, &m_height, &m_channels, 0);

        if (i > 0 && (width != m_width || height != m_height || channels != m_channels))
        {
            if (data) stbi_image_free(data);
            glCALL(glDeleteTextures(1, &m_id));
            VAMP_ERROR("[CubeMap] Cube images must all have the same size and number of channels. Check your textures!");
            return;
        }

        width = m_width;
        height = m_height;
        channels = m_channels;

        if (data)
        {
            glCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA, m_width, m_height, 0, GetTextureFormat(m_channels), GL_UNSIGNED_BYTE, data));
            stbi_image_free(data);
        }
    }

    glCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

LearnOpenGL::CubeMap::~CubeMap()
{
    glCALL(glDeleteTextures(1, &m_id));
}



void LearnOpenGL::CubeMap::Bind(unsigned int unit)
{
    glCALL(glActiveTexture(GL_TEXTURE0 + unit));
    glCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_id));
}

void LearnOpenGL::CubeMap::UnBind()
{   
    glCALL(glActiveTexture(GL_TEXTURE0));
    glCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}