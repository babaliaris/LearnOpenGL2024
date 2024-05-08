#pragma once
#include <string>

namespace LearnOpenGL
{
    enum TextureTypeE
    {
        NONE, DIFFUSE, SPECULAR, COLOR_RGB,
        COLOR_RGBA, DEPTH, STENCIL, DEPTH_STENCIL
    };


    class Texture
    {
        public:
        Texture(const std::string &filepath);
        Texture(TextureTypeE type, int width, int height);
        ~Texture();

        void Bind(unsigned int unit = 0);
        void UnBind();

        inline void setType(TextureTypeE type) {m_type = type;}

        inline int GetWidth() {return m_width;}
        inline int GetHeight() {return m_height;}
        inline int GetChannels() {return m_channels;}
        inline unsigned int getId() const {return m_id;}
        inline const std::string &GetFilepath(){return m_filepath;}
        inline TextureTypeE getType() const {return m_type;}

        private:
        unsigned int m_id;
        int m_width, m_height, m_channels;
        std::string m_filepath;
        TextureTypeE m_type;
    };
}