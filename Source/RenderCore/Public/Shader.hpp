#pragma once

#include "BaseTypes.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

namespace spy
{
/**
 * @brief A shader program.
 */
class RENDER_CORE_API Shader
{
public:

    enum class Type
    {
        VERTEX_SHADER,
        GEOMETRY_SHADER,
        TESSELATION_CONTROL_SHADER,
        TESSELATION_EVALUATION_SHADER,
        FRAGMENT_SHADER
    };

public:

    /**
     * @brief Creates a shader.
     */
    Shader();

    /**
     * @brief Destroys a shader.
     */
    virtual ~Shader();

    /**
     * @brief Get the location of a uniform.
     *
     * @param name Name of the uniform.
     * @return Location of a uniform.
     */
    uint32 GetUniformLocation(const std::string& name) const;

    bool LinkProgram();

    /**
     * @brief Load shader from a file.
     *
     * @param vertexShaderFilename Name and path to the vertex shader file.
     * @param type Type of shader.
     * @return True if everything went successfully. False if not.
     */
    bool LoadShaderFromFile(const std::string& shaderFilename, Type type);

    /**
     * @brief Load shader from a string.
     *
     * @param vertexShaderSource Vertex shader source code.
     * @param type Type of shader.
     * @return True if everything went successfully. False if not.
     */
    bool LoadShaderFromString(const std::string& shaderSource, Type type);

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
   
    static bool CheckShaderCompileErrors(uint32 shader, const std::string& type);

private:

    uint32 m_shaderProgram;
    std::vector<uint32> m_shaders;
};
} // namespace spy

/**
 * @class spy::Shader
 * @ingroup RenderCore
 */
