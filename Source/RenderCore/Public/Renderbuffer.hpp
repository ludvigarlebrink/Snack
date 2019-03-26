#pragma once

#include "BaseTypes.hpp"

namespace spy
{
class RENDER_CORE_API Renderbuffer final
{
public:

    enum class InternalFormat
    {
        DEPTH24_STENCIL8
    };

public:

    Renderbuffer();

    ~Renderbuffer();

    void Bind();

    uint32 GetHandle() const;

    void SetData(int32 width, int32 height, InternalFormat internalFormat);

private:

    uint32 ToGLInternalFormat(InternalFormat internalFormat);

    void SetUp();

    void TearDown();

private:

    InternalFormat m_internalFormat;
    uint32 m_rbo;
    int32 m_width;
    int32 m_height;
};
} // namespace spy
