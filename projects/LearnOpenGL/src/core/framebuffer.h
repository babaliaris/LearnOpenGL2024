#pragma once

namespace LearnOpenGL
{
    class Texture;
    class RenderBuffer;

    class FrameBuffer
    {
        public:
        enum TypeE
        {
            COLOR_RGB, COLOR_RGBA,
            COLOR_RGB_TEXTURE, COLOR_RGBA_TEXTURE,
            COLOR_RGB_DEPTH_TEXTURE, COLOR_RGBA_DEPTH_TEXTURE,
            COLOR_RGB_TEXTURE_DEPTH_TEXTURE, COLOR_RGBA_TEXTURE_DEPTH_TEXTURE,
        };

        public:
        FrameBuffer(FrameBuffer::TypeE type, int width, int height);
        ~FrameBuffer();

        void Bind();
        void UnBind();

        inline Texture *getColorTexture() const {return m_color_texture;}
        inline Texture *getDepthTexture() const {return m_depth_texture;}

        private:
        unsigned int m_id;
        Texture *m_color_texture, *m_depth_texture;
        RenderBuffer *m_color_buffer, *m_stencil_buffer, *m_depth_stencil_buffer;
    };
}