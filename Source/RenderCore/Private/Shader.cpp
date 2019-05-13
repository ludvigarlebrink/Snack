#include "Shader.hpp"
#include "Log.hpp"
#include "RenderError.hpp"
#include "RenderSM.hpp"
#include "glad/glad.h"

#include <fstream>
#include <streambuf>

namespace snack
{
Shader::Shader()
    : m_shaderProgram(0u)
{
    m_shaderProgram = glCreateProgram();
    SPY_CHECK_RENDER_ERROR();
}

Shader::~Shader()
{
    if (m_shaderProgram)
    {
        glDeleteProgram(m_shaderProgram);
        SPY_CHECK_RENDER_ERROR();
        m_shaderProgram = 0u;
    }
}

uint32 Shader::GetUniformLocation(const std::string& name) const
{
    uint32 returnVal = glGetUniformLocation(m_shaderProgram, name.c_str());
    SPY_CHECK_RENDER_ERROR();
    return returnVal;
}

bool Shader::LinkProgram()
{
    glLinkProgram(m_shaderProgram);
    SPY_CHECK_RENDER_ERROR();
    if (!CheckProgramLinkErrors(m_shaderProgram))
    {
        for (auto s : m_shaders)
        {
            glDeleteShader(s);
            SPY_CHECK_RENDER_ERROR();
        }
        glDeleteProgram(m_shaderProgram);
        SPY_CHECK_RENDER_ERROR();
        m_shaderProgram = 0u;

        return false;
    }

    for (auto s : m_shaders)
    {
        glDeleteShader(s);
        SPY_CHECK_RENDER_ERROR();
    }

    return true;
}

bool Shader::LoadShaderFromFile(const std::string& shaderFilename, Type type)
{
    std::ifstream f(shaderFilename);
    if (!f.is_open())
    {
        return false;
    }

    std::string source((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();

    return LoadShaderFromString(source, "In file " + shaderFilename + "\n", type);
}

bool Shader::LoadShaderFromString(const std::string& shaderSource, Type type)
{
	return LoadShaderFromString(shaderSource, "", type);
}

bool Shader::LoadShaderFromString(const std::string& shaderSource, const std::string& debugInfo, Type type)
{
    uint32 shader = 0u;
    switch (type)
    {
    case Type::VERTEX_SHADER:
        shader = glCreateShader(GL_VERTEX_SHADER);
        SPY_CHECK_RENDER_ERROR();
        break;
    case Type::GEOMETRY_SHADER:
        shader = glCreateShader(GL_GEOMETRY_SHADER);
        SPY_CHECK_RENDER_ERROR();
        break;
    case Type::TESSELATION_CONTROL_SHADER:
        shader = glCreateShader(GL_TESS_CONTROL_SHADER);
        SPY_CHECK_RENDER_ERROR();
        break;
    case Type::TESSELATION_EVALUATION_SHADER:
        shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
        SPY_CHECK_RENDER_ERROR();
        break;
    case Type::FRAGMENT_SHADER:
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        SPY_CHECK_RENDER_ERROR();
        break;
    default:
        break;
    }

    const char* sharderChars = shaderSource.c_str();
    glShaderSource(shader, 1, &sharderChars, NULL);
    SPY_CHECK_RENDER_ERROR();
    glCompileShader(shader);
    SPY_CHECK_RENDER_ERROR();
    if (!CheckShaderCompileErrors(shader, debugInfo))
    {
        for (auto s : m_shaders)
        {
            glDeleteShader(s);
        }
        glDeleteShader(shader);
        SPY_CHECK_RENDER_ERROR();
        glDeleteProgram(m_shaderProgram);
        SPY_CHECK_RENDER_ERROR();
        m_shaderProgram = 0u;
        return false;
    }

    glAttachShader(m_shaderProgram, shader);
    SPY_CHECK_RENDER_ERROR();

    m_shaders.push_back(shader);
    
    return true;
}

void Shader::SetFloat(uint32 location, f32 value)
{
    Use();
    glUniform1f(location, value);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetFloatSlow(const std::string& name, f32 value)
{
    Use();
    glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetFloatSlow(const std::string& name, const std::vector<f32>& values)
{
    Use();
    glUniform1fv(glGetUniformLocation(m_shaderProgram, name.c_str()), values.size(), values.data());
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetInt(uint32 location, int32 value)
{
    Use();
    glUniform1i(location, value);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetIntSlow(const std::string& name, int32 value)
{
    Use();
    glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetMat2(uint32 location, const glm::mat2& mat)
{
    Use();
    glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetMat2Slow(const std::string& name, const glm::mat2& mat)
{
    Use();
    glUniformMatrix2fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetMat3(uint32 location, const glm::mat3& mat)
{
    Use();
    glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetMat3Slow(const std::string& name, const glm::mat3& mat)
{
    Use();
    glUniformMatrix3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetMat4(uint32 location, const glm::mat4& mat)
{
    Use();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetMat4Slow(const std::string& name, const glm::mat4& mat)
{
    Use();
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetVec2(uint32 location, const glm::vec2& vec)
{
    Use();
    glUniform2fv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetVec2Slow(const std::string& name, const glm::vec2& vec)
{
    Use();
    glUniform2fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetIVec2(uint32 location, const glm::ivec2& vec)
{
    Use();
    glUniform2iv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetIVec2Slow(const std::string& name, const glm::ivec2& vec)
{
    Use();
    glUniform2iv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetUVec2(uint32 location, const glm::uvec2& vec)
{
    Use();
    glUniform2uiv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetUVec2Slow(const std::string& name, const glm::uvec2& vec)
{
    Use();
    glUniform2uiv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetVec3(uint32 location, const glm::vec3& vec)
{
    Use();
    glUniform3fv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetVec3Slow(const std::string& name, const glm::vec3& vec)
{
    Use();
    glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetVec3Slow(const std::string& name, const std::vector<glm::vec3>& vec)
{
    Use();
    glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), vec.size(), &vec[0][0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetIVec3(uint32 location, const glm::ivec3& vec)
{
    Use();
    glUniform3iv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetIVec3Slow(const std::string& name, const glm::ivec3& vec)
{
    Use();
    glUniform3iv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetUVec3(uint32 location, const glm::uvec3& vec)
{
    Use();
    glUniform3uiv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetUVec3Slow(const std::string& name, const glm::uvec3& vec)
{
    Use();
    glUniform3uiv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetVec4(uint32 location, const glm::vec4& vec)
{
    Use();
    glUniform4fv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetVec4Slow(const std::string& name, const glm::vec4& vec)
{
    Use();
    glUniform4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetIVec4(uint32 location, const glm::ivec4& vec)
{
    Use();
    glUniform4iv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetIVec4Slow(const std::string& name, const glm::ivec4& vec)
{
    Use();
    glUniform4iv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetUVec4(uint32 location, const glm::uvec4& vec)
{
    Use();
    glUniform4uiv(location, 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::SetUVec4Slow(const std::string& name, const glm::uvec4& vec)
{
    Use();
    glUniform4uiv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &vec[0]);
    SPY_CHECK_RENDER_ERROR();
}

void Shader::Use()
{
    RenderSM::UseShaderProgram(m_shaderProgram);
}

bool Shader::CheckProgramLinkErrors(uint32 program)
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

bool Shader::CheckShaderCompileErrors(uint32 shader, const std::string& type)
{
    int32 success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    SPY_CHECK_RENDER_ERROR();
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        SPY_CHECK_RENDER_ERROR();
        SPY_LOG(type << "ERROR: " << infoLog << "\n");
        return false;
    }

    return true;
}
} // namespace snack
