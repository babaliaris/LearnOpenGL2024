#pragma once

namespace LearnOpenGL
{
    enum RenderBufferTypeE
    {
        NONE, DEPTH, STENCIL, 
        DEPTH_STENCIL, COLOR
    };


    class RenderBuffer
    {
        public:
        RenderBuffer(RenderBufferTypeE type, int width, int height);
        ~RenderBuffer();

        void Bind();
        void UnBind();

        inline unsigned int getId() const {return m_id;}

        private:
        unsigned int m_id;
    };
}