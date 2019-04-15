#pragma once

#include "BaseTypes.hpp"

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace snack
{
class RENDER_CORE_API ComputeShader
{
public:

    ComputeShader();

    ~ComputeShader();

    /**
     * @brief Dispatch the compute shader.
     * @param xWorkgroupCount Number of workgroups.
     * @param yWorkgroupCount Number of workgroups.
     * @param zWorkgroupCount Number of workgroups.
     */
    void Dispatch(uint32 xWorkgroupCount, uint32 yWorkgroupCount, uint32 zWorkgroupCount);

    /**
     * @brief Load shader from a file.
     *
     * @param vertexShaderFilename Name and path to the vertex shader file.
     * @return True if everything went successfully. False if not.
     */
    bool LoadShaderFromFile(const std::string& shaderFilename);

    /**
     * @brief Load shader from a string.
     *
     * @param vertexShaderSource Vertex shader source code.
     * @return True if everything went successfully. False if not.
     */
    bool LoadShaderFromString(const std::string& shaderSource);

    /**
     * @brief Set a float uniform.
     *
     * @param location Location of uniform.
     * @param value Float.
     */
    void SetFloat(uint32 location, f32 value);

    /**
     * @brief Set a float uniform, slow.
     *
     * @param name Name of uniform.
     * @param value Float.
     */
    void SetFloatSlow(const std::string& name, f32 value);

    void SetFloatSlow(const std::string& name, const std::vector<f32>& values);

    /**
     * @brief Set a int uniform.
     *
     * @param location Location of uniform.
     * @param value Int.
     */
    void SetInt(uint32 location, int32 value);

    /**
     * @brief Set a int uniform, slow.
     *
     * @param name Name of uniform.
     * @param value Int.
     */
    void SetIntSlow(const std::string& name, int32 value);

    /**
     * @brief Set a matrix uniform.
     *
     * @param location Location of uniform.
     * @param mat Matrix.
     */
    void SetMat2(uint32 location, const glm::mat2& mat);

    /**
     * @brief Set a matrix uniform, slow.
     *
     * @param name Name of uniform.
     * @param mat Matrix.
     */
    void SetMat2Slow(const std::string& name, const glm::mat2& mat);

    /**
     * @brief Set a matrix uniform.
     *
     * @param location Location of uniform.
     * @param mat Matrix.
     */
    void SetMat3(uint32 location, const glm::mat3& mat);

    /**
     * @brief Set a matrix uniform, slow.
     *
     * @param name Name of uniform.
     * @param mat Matrix.
     */
    void SetMat3Slow(const std::string& name, const glm::mat3& mat);

    /**
     * @brief Set a matrix uniform.
     *
     * @param location Location of uniform.
     * @param mat Matrix.
     */
    void SetMat4(uint32 location, const glm::mat4& mat);

    /**
     * @brief Set a matrix uniform, slow.
     *
     * @param name Name of uniform.
     * @param mat Matrix.
     */
    void SetMat4Slow(const std::string& name, const glm::mat4& mat);

    /**
     * @brief Set a vector uniform.
     *
     * @param location Location of uniform.
     * @param vec Vector.
     */
    void SetVec2(uint32 location, const glm::vec2& vec);

    /**
     * @brief Set a vector uniform, slow.
     *
     * @param name Name of uniform.
     * @param vec Vector.
     */
    void SetVec2Slow(const std::string& name, const glm::vec2& vec);

    /**
     * @brief Set a vector uniform.
     *
     * @param location Location of uniform.
     * @param vec Vector.
     */
    void SetIVec2(uint32 location, const glm::ivec2& vec);

    /**
     * @brief Set a vector uniform, slow.
     *
     * @param name Name of uniform.
     * @param vec Vector.
     */
    void SetIVec2Slow(const std::string& name, const glm::ivec2& vec);

    /**
     * @brief Set a vector uniform.
     *
     * @param location Location of uniform.
     * @param vec Vector.
     */
    void SetUVec2(uint32 location, const glm::uvec2& vec);

    /**
     * @brief Set a vector uniform, slow.
     *
     * @param name Name of uniform.
     * @param vec Vector.
     */
    void SetUVec2Slow(const std::string& name, const glm::uvec2& vec);

    /**
     * @brief Set a vector uniform.
     *
     * @param location Location of uniform.
     * @param vec Vector.
     */
    void SetVec3(uint32 location, const glm::vec3& vec);

    /**
     * @brief Set a vector uniform, slow.
     *
     * @param name Name of uniform.
     * @param vec Vector.
     */
    void SetVec3Slow(const std::string& name, const glm::vec3& vec);

    void SetVec3Slow(const std::string& name, const std::vector<glm::vec3>& vec);

    /**
     * @brief Set a vector uniform.
     *
     * @param location Location of uniform.
     * @param vec Vector.
     */
    void SetIVec3(uint32 location, const glm::ivec3& vec);

    /**
     * @brief Set a vector uniform, slow.
     *
     * @param name Name of uniform.
     * @param vec Vector.
     */
    void SetIVec3Slow(const std::string& name, const glm::ivec3& vec);

    /**
     * @brief Set a vector uniform.
     *
     * @param location Location of uniform.
     * @param vec Vector.
     */
    void SetUVec3(uint32 location, const glm::uvec3& vec);

    /**
     * @brief Set a vector uniform, slow.
     *
     * @param name Name of uniform.
     * @param vec Vector.
     */
    void SetUVec3Slow(const std::string& name, const glm::uvec3& vec);

    /**
     * @brief Set a vector uniform.
     *
     * @param location Location of uniform.
     * @param vec Vector.
     */
    void SetVec4(uint32 location, const glm::vec4& vec);

    /**
     * @brief Set a vector uniform, slow.
     *
     * @param name Name of uniform.
     * @param vec Vector.
     */
    void SetVec4Slow(const std::string& name, const glm::vec4& vec);

    /**
     * @brief Set a vector uniform.
     *
     * @param location Location of uniform.
     * @param vec Vector.
     */
    void SetIVec4(uint32 location, const glm::ivec4& vec);

    /**
     * @brief Set a vector uniform, slow.
     *
     * @param name Name of uniform.
     * @param vec Vector.
     */
    void SetIVec4Slow(const std::string& name, const glm::ivec4& vec);

    /**
     * @brief Set a vector uniform.
     *
     * @param location Location of uniform.
     * @param vec Vector.
     */
    void SetUVec4(uint32 location, const glm::uvec4& vec);

    /**
     * @brief Set a vector uniform, slow.
     *
     * @param name Name of uniform.
     * @param vec Vector.
     */
    void SetUVec4Slow(const std::string& name, const glm::uvec4& vec);

    /**
     * @brief Use this shader.
     */
    void Use();

private:

    static bool CheckProgramLinkErrors(uint32 program);

    static bool CheckShaderCompileErrors(uint32 shader);

private:

    uint32 m_shaderProgram;
};
} // namespace snack
