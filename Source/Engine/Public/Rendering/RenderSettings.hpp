#pragma once

namespace snack
{
class ENGINE_API RenderSettings
{
public:

    enum class GBufferSize
    {
        U8,
        F16,
        F32
    };

public:

    static GBufferSize GetGAlbedoBufferSize();

    static GBufferSize GetGNormalBufferSize();

    static GBufferSize GetGPositionBufferSize();

private:

    static GBufferSize m_gAlbedoBufferSize;
    static GBufferSize m_gNormalBufferSize;
    static GBufferSize m_gPositionBufferSize;
};
} // namespace snack
