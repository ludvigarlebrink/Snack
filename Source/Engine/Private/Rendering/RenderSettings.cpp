#include "Rendering/RenderSettings.hpp"

namespace snack
{
RenderSettings::GBufferSize RenderSettings::m_gAlbedoBufferSize = GBufferSize::U8;
RenderSettings::GBufferSize RenderSettings::m_gNormalBufferSize = GBufferSize::F32;
RenderSettings::GBufferSize RenderSettings::m_gPositionBufferSize = GBufferSize::F32;

RenderSettings::GBufferSize RenderSettings::GetGAlbedoBufferSize()
{
    return m_gAlbedoBufferSize;
}

RenderSettings::GBufferSize RenderSettings::GetGNormalBufferSize()
{
    return m_gNormalBufferSize;
}

RenderSettings::GBufferSize RenderSettings::GetGPositionBufferSize()
{
    return m_gPositionBufferSize;
}
} // namespace snack
