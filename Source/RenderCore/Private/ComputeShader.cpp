#include "ComputeShader.hpp"
#include "glad/glad.h"

namespace spy
{
ComputeShader::ComputeShader()
{
    m_program = glCreateProgram();
}

ComputeShader::~ComputeShader()
{
    glDeleteProgram(m_program);
}

void ComputeShader::Dispatch(uint32 xWorkgroupCount, uint32 yWorkgroupCount, uint32 zWorkgroupCount)
{
    glDispatchCompute(xWorkgroupCount, yWorkgroupCount, zWorkgroupCount)
}
} // namespace spy
