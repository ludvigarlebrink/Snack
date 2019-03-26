#pragma once

#include "BaseTypes.hpp"
#include "Texture.hpp"

#include <vector>

namespace spy
{
/**
 * @brief A framebuffer.
 */
class RENDER_CORE_API FullScreenQuad
{
public:

    FullScreenQuad();

    virtual ~FullScreenQuad();

    void Bind();

    void Render();

private:

    void SetUp();

    void TearDown();

private:

    uint32 m_vao;
    uint32 m_vbo;
};
} // namespace spy
