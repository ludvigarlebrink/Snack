#pragma once

#include "BaseTypes.hpp"

namespace spy
{
class RENDER_CORE_API ComputeShader
{
public:

    ComputeShader();

    ~ComputeShader();

    void Dispatch(uint32 xWorkgroupCount, uint32 yWorkgroupCount, uint32 zWorkgroupCount);

private:

    uint32 m_program;
};
} // namespace spy
