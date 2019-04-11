#include "ComputeShader.hpp"
#include "Log.hpp"
#include "RenderError.hpp"
#include "glad/glad.h"

#include <fstream>
#include <streambuf>

namespace snack
{
ComputeShader::ComputeShader()
{
    m_shaderProgram = glCreateProgram();
}

ComputeShader::~ComputeShader()
{
    glDeleteProgram(m_shaderProgram);
}

void ComputeShader::Dispatch(uint32 xWorkgroupCount, uint32 yWorkgroupCount, uint32 zWorkgroupCount)
{
    glDispatchCompute(xWorkgroupCount, yWorkgroupCount, zWorkgroupCount);
}

bool ComputeShader::LoadShaderFromFile(const std::string& shaderFilename)
{
    std::ifstream f(shaderFilename);
    if (!f.is_open())
    {
        return false;
    }

    std::string source((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();

    return LoadShaderFromString(source);
}

bool ComputeShader::LoadShaderFromString(const std::string& shaderSource)
{
    uint32 shader = glCreateShader(GL_COMPUTE_SHADER);
    const char* sharderChars = shaderSource.c_str();
    glShaderSource(shader, 1, &sharderChars, NULL);
    SPY_CHECK_RENDER_ERROR();
    glCompileShader(shader);
    SPY_CHECK_RENDER_ERROR();

    glAttachShader(m_shaderProgram, shader);
    SPY_CHECK_RENDER_ERROR();
    
    return true;
}

void ComputeShader::SetFloat(uint32 location, f32 value)
{
    Use();
    glUniform1f(location, value);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetFloatSlow(const std::string& name, f32 value)
{
    Use();
    glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetFloatSlow(const std::string& name, const std::vector<f32>& values)
{
    Use();
    glUniform1fv(glGetUniformLocation(m_shaderProgram, name.c_str()), values.size(), values.data());
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetInt(uint32 location, int32 value)
{
    Use();
    glUniform1i(location, value);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetIntSlow(const std::string& name, int32 value)
{
    Use();
    glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetMat2(uint32 location, const glm::mat2& mat)
{
    Use();
    glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetMat2Slow(const std::string& name, const glm::mat2& mat)
{
    Use();
    glUniformMatrix2fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetMat3(uint32 location, const glm::mat3& mat)
{
    Use();
    glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetMat3Slow(const std::string& name, const glm::mat3& mat)
{
    Use();
    glUniformMatrix3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetMat4(uint32 location, const glm::mat4& mat)
{
    Use();
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetMat4Slow(const std::string& name, const glm::mat4& mat)
{
    Use();
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetVec2(uint32 location, const glm::vec2& vec)
{
    Use();
    glUniform2fv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetVec2Slow(const std::string& name, const glm::vec2& vec)
{
    Use();
    glUniform2fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetIVec2(uint32 location, const glm::ivec2& vec)
{
    Use();
    glUniform2iv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetIVec2Slow(const std::string& name, const glm::ivec2& vec)
{
    Use();
    glUniform2iv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetUVec2(uint32 location, const glm::uvec2& vec)
{
    Use();
    glUniform2uiv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetUVec2Slow(const std::string& name, const glm::uvec2& vec)
{
    Use();
    glUniform2uiv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetVec3(uint32 location, const glm::vec3& vec)
{
    Use();
    glUniform3fv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetVec3Slow(const std::string& name, const glm::vec3& vec)
{
    Use();
    glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetVec3Slow(const std::string& name, const std::vector<glm::vec3>& vec)
{
    Use();
    glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), vec.size(), &vec[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetIVec3(uint32 location, const glm::ivec3& vec)
{
    Use();
    glUniform3iv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetIVec3Slow(const std::string& name, const glm::ivec3& vec)
{
    Use();
    glUniform3iv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetUVec3(uint32 location, const glm::uvec3& vec)
{
    Use();
    glUniform3uiv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetUVec3Slow(const std::string& name, const glm::uvec3& vec)
{
    Use();
    glUniform3uiv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetVec4(uint32 location, const glm::vec4& vec)
{
    Use();
    glUniform4fv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetVec4Slow(const std::string& name, const glm::vec4& vec)
{
    Use();
    glUniform4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetIVec4(uint32 location, const glm::ivec4& vec)
{
    Use();
    glUniform4iv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetIVec4Slow(const std::string& name, const glm::ivec4& vec)
{
    Use();
    glUniform4iv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetUVec4(uint32 location, const glm::uvec4& vec)
{
    Use();
    glUniform4uiv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::SetUVec4Slow(const std::string& name, const glm::uvec4& vec)
{
    Use();
    glUniform4uiv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void ComputeShader::Use()
{
    glUseProgram(m_shaderProgram);
    SPY_CHECK_RENDER_ERROR();
}
bool ComputeShader::CheckProgramLinkErrors(uint32 program)
{
    int32 success;
    char infoLog[1024];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    SPY_CHECK_RENDER_ERROR();
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        SPY_CHECK_RENDER_ERROR();
        SPY_LOG("Program ERROR: " << infoLog << "\n");
        return false;
    }

    return true;
}
bool ComputeShader::CheckShaderCompileErrors(uint32 shader)
{
    int32 success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    SPY_CHECK_RENDER_ERROR();
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        SPY_CHECK_RENDER_ERROR();
        SPY_LOG("COMPUTE SHADER ERROR: " << infoLog << "\n");
        return false;
    }

    return true;
}
} // namespace snack
