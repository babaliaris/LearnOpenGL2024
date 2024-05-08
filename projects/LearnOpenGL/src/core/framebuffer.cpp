#include "framebuffer.h"
#include <glad/glad.h>
#include "../debug/glcall.h"
#include "render_buffer.h"
#include "texture.h"
#include <vamplogger/logger.h>


namespace LearnOpenGL
{
    FrameBuffer::FrameBuffer(FrameBuffer::TypeE type, int width, int height)
    : m_id(0), m_color_texture(nullptr), m_depth_texture(nullptr),
      m_color_buffer(nullptr), m_stencil_buffer(nullptr), m_depth_stencil_buffer(nullptr)
    {
        glCALL(glGenFramebuffers(1, &m_id));
        glCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_id));

        switch (type)
        {
            case FrameBuffer::TypeE::COLOR_RGB:
            {
                m_color_buffer = new RenderBuffer(RenderBuffer::TypeE::COLOR_RGB, width, height);
                m_depth_stencil_buffer = new RenderBuffer(RenderBuffer::TypeE::DEPTH_STENCIL, width, height);

                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_color_buffer->getId()));
                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth_stencil_buffer->getId()));
                break;
            }

            case FrameBuffer::TypeE::COLOR_RGBA:
            {
                m_color_buffer = new RenderBuffer(RenderBuffer::TypeE::COLOR_RGBA, width, height);
                m_depth_stencil_buffer = new RenderBuffer(RenderBuffer::TypeE::DEPTH_STENCIL, width, height);

                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_color_buffer->getId()));
                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth_stencil_buffer->getId()));
                break;
            }

            case FrameBuffer::TypeE::COLOR_RGB_TEXTURE:
            {
                m_color_texture = new Texture(TextureTypeE::COLOR_RGB, width, height);
                m_depth_stencil_buffer = new RenderBuffer(RenderBuffer::TypeE::DEPTH_STENCIL, width, height);

                glCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture->getId(), 0));
                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth_stencil_buffer->getId()));
            }

            case FrameBuffer::TypeE::COLOR_RGBA_TEXTURE:
            {
                m_color_texture = new Texture(TextureTypeE::COLOR_RGBA, width, height);
                m_depth_stencil_buffer = new RenderBuffer(RenderBuffer::TypeE::DEPTH_STENCIL, width, height);

                glCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture->getId(), 0));
                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth_stencil_buffer->getId()));
            }

            case FrameBuffer::TypeE::COLOR_RGB_DEPTH_TEXTURE:
            {
                m_color_buffer      = new RenderBuffer(RenderBuffer::TypeE::COLOR_RGB, width, height);
                m_depth_texture     = new Texture(TextureTypeE::DEPTH, width, height);
                m_stencil_buffer    = new RenderBuffer(RenderBuffer::TypeE::STENCIL, width, height);

                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_color_buffer->getId()));
                glCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture->getId(), 0));
                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_buffer->getId()));
            }


            case FrameBuffer::TypeE::COLOR_RGBA_DEPTH_TEXTURE:
            {
                m_color_buffer      = new RenderBuffer(RenderBuffer::TypeE::COLOR_RGBA, width, height);
                m_depth_texture     = new Texture(TextureTypeE::DEPTH, width, height);
                m_stencil_buffer    = new RenderBuffer(RenderBuffer::TypeE::STENCIL, width, height);

                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_color_buffer->getId()));
                glCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture->getId(), 0));
                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_buffer->getId()));
            }


            case FrameBuffer::TypeE::COLOR_RGB_TEXTURE_DEPTH_TEXTURE:
            {
                m_color_texture     = new Texture(TextureTypeE::COLOR_RGB, width, height);
                m_depth_texture     = new Texture(TextureTypeE::DEPTH, width, height);
                m_stencil_buffer    = new RenderBuffer(RenderBuffer::TypeE::STENCIL, width, height);

                glCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture->getId(), 0));
                glCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture->getId(), 0));
                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_buffer->getId()));
            }


            case FrameBuffer::TypeE::COLOR_RGBA_TEXTURE_DEPTH_TEXTURE:
            {
                m_color_texture     = new Texture(TextureTypeE::COLOR_RGBA, width, height);
                m_depth_texture     = new Texture(TextureTypeE::DEPTH, width, height);
                m_stencil_buffer    = new RenderBuffer(RenderBuffer::TypeE::STENCIL, width, height);

                glCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture->getId(), 0));
                glCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture->getId(), 0));
                glCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_buffer->getId()));
            }
            
            default:
            {
                VAMP_ERROR("[FrameBuffer] Uknown FrameBufferTypeE.");
                break;
            }
        }

        glCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }


    FrameBuffer::~FrameBuffer()
    {
        glCALL(glDeleteFramebuffers(1, &m_id));
        if (m_color_texture) delete m_color_texture;
        if (m_depth_texture) delete m_depth_texture;
        if (m_color_buffer) delete m_color_buffer;
        if (m_stencil_buffer) delete m_stencil_buffer;
        if (m_depth_stencil_buffer) delete m_depth_stencil_buffer;
    }

    void FrameBuffer::Bind()
    {
        glCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
    }


    void FrameBuffer::UnBind()
    {
        glCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }
}