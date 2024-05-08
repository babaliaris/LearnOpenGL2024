#pragma once
#include <string>
#include <vector>

namespace LearnOpenGL
{
    class CubeMap
    {
        public:
        CubeMap(const std::vector<std::string> &paths, bool flipImages = false);
        ~CubeMap();

        void Bind(unsigned int unit = 0);
        void UnBind();

        inline int GetWidth() {return m_width;}
        inline int GetHeight() {return m_height;}
        inline int GetChannels() {return m_channels;}
        inline unsigned int getId() const {return m_id;}

        private:
        unsigned int m_id;
        int m_width, m_height, m_channels;
        std::vector<std::string>m_filepaths;
    };
}