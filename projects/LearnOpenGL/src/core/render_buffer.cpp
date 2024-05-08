#include "render_buffer.h"
#include "glad/glad.h"
#include "../debug/glcall.h"
#include <vamplogger/logger.h>


namespace LearnOpenGL
{
    RenderBuffer::RenderBuffer(RenderBuffer::TypeE type, int width, int height)
    : m_id(0)
    {
        glCALL(glGenRenderbuffers(1, &m_id));
        glCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_id));
        
        switch (type)
        {
            case RenderBuffer::TypeE::COLOR_RGB:
            {
                glCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, width, height));
                break;
            }

            case RenderBuffer::TypeE::COLOR_RGBA:
            {
                glCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height));
                break;
            }

            case RenderBuffer::TypeE::DEPTH:
            {
                glCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height));
                break;
            }

            case RenderBuffer::TypeE::STENCIL:
            {
                glCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, width, height));
                break;
            }

            case RenderBuffer::TypeE::DEPTH_STENCIL:
            {
                glCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
                break;
            }
            
            default:
            {
                VAMP_ERROR("[RenderBuffer] Uknown RenderBuffer::TypeE");
                break;
            }
        }

        glCALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
    }


    RenderBuffer::~RenderBuffer()
    {
        glCALL(glDeleteRenderbuffers(1, &m_id));
    }


    void RenderBuffer::Bind()
    {
        glCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_id));
    }


    void RenderBuffer::UnBind()
    {
        glCALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
    }
}