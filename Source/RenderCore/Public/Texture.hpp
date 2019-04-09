#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace snack
{
/**
 * @brief A texture.
 */
class RENDER_CORE_API Texture
{
public:

    enum class Format
    {
        R,
        RG,
        RGB,
        RGBA,
    };

    enum class InternalFormat
    {
        R,
        R16F,
        R32F,
        RG,
        RG16F,
        RG32F,
        RGB,
        RGB16F,
        RGB32F,
        RGBA,
        RGBA16F,
        RGBA32F
    };

    enum class Type
    {
        FLOAT,
        UNSIGNED_BYTE
    };

    enum class Wrapping
    {
        CLAMP_TO_EDGE,
        REPEAT,
    };

public:

    /**
     * @brief Creates a texture.
     */
    Texture();

    /**
     * @brief Destroys a texture.
     */
    virtual ~Texture();

    void Bind();

    void Bind(uint32 location);

    InternalFormat GetInternalFormat() const;

    uint32 GetHandle() const;

    int32 GetHeight() const;

    int32 GetWidth() const;
    
    bool LoadFromFile(const std::string& filename, InternalFormat internalFormat, Format format, Type type);

    void SetData(int32 width, int32 height, InternalFormat internalFormat, Format format, Type type, void* pixels);

    void SetSubData(int32 xOffset, int32 yOffset, int32 width, int32 height, Format format, void* pixels);

    /**
     * @brief Set the s wrapping of this texture.
     * @param wrapping Specified wrapping method.
     * @note Texture has to be bound.
     */
    void SetSWrapping(Wrapping wrapping);

    /**
     * @brief Set the t wrapping of this texture.
     * @param wrapping Specified wrapping method.
     * @note Texture has to be bound.
     */
    void SetTWrapping(Wrapping wrapping);

    void Unbind();

private:

    void SetUp();

    void TearDown();

    static uint32 ToGLFormat(Format format);

    static uint32 ToGLInternalFormat(InternalFormat internalFormat);

    static uint32 ToGLType(Type type);

    static uint32 ToGLWrapping(Wrapping wrapping);

private:

    InternalFormat m_internalFormat;
    Type m_type;
    int32 m_height;
    int32 m_width;
    uint32 m_texture;

    Wrapping m_sWrapping;
    Wrapping m_tWrapping;
};
} // namespace snack
