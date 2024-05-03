#pragma once
#include <string>

namespace LearnOpenGL
{
    class Texture
    {
        public:
        Texture(const std::string &filepath);
        ~Texture();

        void Bind(unsigned int unit = 0);
        void UnBind();

        inline int GetWidth() {return m_width;}
        inline int GetHeight() {return m_height;}
        inline int GetChannels() {return m_channels;}
        inline const std::string &GetFilepath(){return m_filepath;}

        private:
        unsigned int m_id;
        int m_width, m_height, m_channels;
        std::string m_filepath;
    };
}