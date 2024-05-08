#pragma once

namespace LearnOpenGL
{

    class RenderBuffer
    {
        public:
        enum TypeE
        {
            NONE, DEPTH, STENCIL, 
            DEPTH_STENCIL, COLOR_RGB, COLOR_RGBA
        };

        public:
        RenderBuffer(TypeE type, int width, int height);
        ~RenderBuffer();

        void Bind();
        void UnBind();

        inline unsigned int getId() const {return m_id;}

        private:
        unsigned int m_id;
    };
}