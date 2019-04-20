#include "Framebuffer.hpp"
#include "RenderError.hpp"
#include "Renderbuffer.hpp"
#include "Texture.hpp"
#include "glad/glad.h"

namespace snack
{
Framebuffer::Framebuffer()
    : m_fbo(0u)
{
    SetUp();
}

Framebuffer::~Framebuffer()
{
    TearDown();
}

void Framebuffer::AttachDepthBuffer(Texture* buffer)
{
    Bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, buffer->GetHandle(), 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    SPY_CHECK_RENDER_ERROR();
}

void Framebuffer::AttachDepthStencil(Renderbuffer* renderbuffer)
{
    Bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->GetHandle());
    SPY_CHECK_RENDER_ERROR();
}

void Framebuffer::AttachTexture(uint32 attachment, Texture* texture)
{
    Bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, texture->GetHandle(), 0);
    SPY_CHECK_RENDER_ERROR();
}

void Framebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    SPY_CHECK_RENDER_ERROR();
}

void Framebuffer::SetDrawBuffers(uint32* attachments, int32 attachmentCount)
{
    Bind();
    uint32* a = new uint32[attachmentCount];
    for (int32 i = 0; i < attachmentCount; ++i)
    {
        a[i] = GL_COLOR_ATTACHMENT0 + attachments[i];
    }
    glDrawBuffers(attachmentCount, a);
    SPY_CHECK_RENDER_ERROR();
    delete[] a;
}

void Framebuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0u);
    SPY_CHECK_RENDER_ERROR();
}

void Framebuffer::SetUp()
{
    TearDown();
    glGenFramebuffers(1, &m_fbo);
    SPY_CHECK_RENDER_ERROR();
}

void Framebuffer::TearDown()
{
    glDeleteFramebuffers(1, &m_fbo);
    SPY_CHECK_RENDER_ERROR();
    m_fbo = 0u;
}
} // namespace snack
