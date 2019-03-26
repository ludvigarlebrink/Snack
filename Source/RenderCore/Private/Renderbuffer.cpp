#include "Renderbuffer.hpp"
#include "RenderError.hpp"
#include "glad/glad.h"

namespace spy
{
Renderbuffer::Renderbuffer()
    : m_internalFormat(InternalFormat::DEPTH24_STENCIL8)
    , m_rbo(0u)
{
    SetUp();
}

Renderbuffer::~Renderbuffer()
{
    TearDown();
}

void Renderbuffer::Bind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    SPY_CHECK_RENDER_ERROR();
}

uint32 Renderbuffer::GetHandle() const
{
    return m_rbo;
}

void Renderbuffer::SetData(int32 width, int32 height, InternalFormat internalFormat)
{
    Bind();
    m_width = width;
    m_height = height;
    glRenderbufferStorage(GL_RENDERBUFFER, ToGLInternalFormat(internalFormat), m_width, m_height);
    SPY_CHECK_RENDER_ERROR();
}

uint32 Renderbuffer::ToGLInternalFormat(InternalFormat internalFormat)
{
    switch (internalFormat)
    {
    case InternalFormat::DEPTH24_STENCIL8:
        return GL_DEPTH24_STENCIL8;
    default:
        break;
    }

    return GL_DEPTH24_STENCIL8;
}

void Renderbuffer::SetUp()
{
    glGenRenderbuffers(1, &m_rbo);
}

void Renderbuffer::TearDown()
{
    glDeleteRenderbuffers(1, &m_rbo);
}
} // namespace spy
