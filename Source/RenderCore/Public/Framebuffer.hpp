#pragma once

#include "BaseTypes.hpp"
#include "Texture.hpp"

#include <vector>

namespace spy
{
class Renderbuffer;

/**
 * @brief A framebuffer.
 */
class RENDER_CORE_API Framebuffer final
{
public:

    Framebuffer();

    ~Framebuffer();

    void AttachDepthStencil(Renderbuffer* renderbuffer);

    void AttachTexture(uint32 attachment, Texture* texture);

    void Bind();

    void Unbind();

private:

    void SetUp();

    void TearDown();

private:

    uint32 m_fbo;
};
} // namespace spy
