#include "Texture.hpp"
#include "RenderSM.hpp"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace spy
{
Texture::Texture()
    : m_internalFormat(InternalFormat::RGBA)
    , m_height(0)
    , m_width(0)
    , m_texture(0u)
{
    SetUp();
}

Texture::~Texture()
{
    TearDown();
}

void Texture::Bind()
{
    RenderSM::BindTexture2D(m_texture);
}

void Texture::Bind(uint32 location)
{
    glActiveTexture(GL_TEXTURE0 + location);
    RenderSM::BindTexture2D(m_texture);
}

Texture::InternalFormat Texture::GetInternalFormat() const
{
    return m_internalFormat;
}

uint32 Texture::GetHandle() const
{
    return m_texture;
}

int32 Texture::GetHeight() const
{
    return m_height;
}

int32 Texture::GetWidth() const
{
    return m_width;
}

bool Texture::LoadFromFile(const std::string& filename, InternalFormat internalFormat, Format format, Type type)
{
    int32 sformat = 0;
    uint8* pData = nullptr;
    
    switch (internalFormat)
    {
    case InternalFormat::R:
        pData = stbi_load(filename.c_str(), &m_width, &m_height, &sformat, STBI_grey);
        break;
    case InternalFormat::RG:
        pData = stbi_load(filename.c_str(), &m_width, &m_height, &sformat, STBI_grey_alpha);
        break;
    case InternalFormat::RGB:
        pData = stbi_load(filename.c_str(), &m_width, &m_height, &sformat, STBI_rgb);
        break;
    case  InternalFormat::RGBA:
        pData = stbi_load(filename.c_str(), &m_width, &m_height, &sformat, STBI_rgb_alpha);
        break;
    default:
        break;
    }

    if (!pData)
    {
        return false;
    }

    Bind();

    m_internalFormat = internalFormat;
    m_type = type;

    glTexImage2D(GL_TEXTURE_2D, 0, ToGLInternalFormat(m_internalFormat), m_width, m_height, 0, ToGLFormat(format), ToGLType(type), pData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pData);

    return true;
}

void Texture::SetData(int32 width, int32 height, InternalFormat internalFormat, Format format, Type type, void* pixels)
{
    m_width = width;
    m_height = height;
    m_internalFormat = internalFormat;
    m_type = type;
    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, ToGLInternalFormat(m_internalFormat), m_width, m_height, 0, ToGLFormat(format), ToGLType(type), pixels);
}

void Texture::SetSubData(int32 xOffset, int32 yOffset, int32 width, int32 height, Format format, void* pixels)
{
    Bind();
    glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, ToGLFormat(format), GL_UNSIGNED_BYTE, pixels);
}

void Texture::SetSWrapping(Wrapping wrapping)
{
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ToGLWrapping(wrapping));
    m_sWrapping = wrapping;
}

void Texture::SetTWrapping(Wrapping wrapping)
{
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ToGLWrapping(wrapping));
    m_tWrapping = wrapping;
}

void Texture::Unbind()
{
    RenderSM::BindTexture2D(0u);
}

void Texture::SetUp()
{
    glGenTextures(1, &m_texture);

    Bind();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::TearDown()
{
   glDeleteTextures(1, &m_texture);
   m_texture = 0u;
}

uint32 Texture::ToGLFormat(Format format)
{
    switch (format)
    {
    case Format::R:
        return GL_RED;
    case Format::RG:
        return GL_RG;
    case Format::RGB:
        return GL_RGB;
    case Format::RGBA:
        return GL_RGBA;
    default:
        break;
    }

    return GL_RGBA;
}

uint32 Texture::ToGLInternalFormat(InternalFormat internalFormat)
{
    switch (internalFormat)
    {
    case InternalFormat::R:
        return GL_RED;
    case InternalFormat::R16F:
        return GL_R16F;
    case InternalFormat::R32F:
        return GL_R32F;
    case InternalFormat::RG:
        return GL_RG;
    case InternalFormat::RG16F:
        return GL_RG16F;
    case InternalFormat::RG32F:
        return GL_RG32F;
    case InternalFormat::RGB:
        return GL_RGB;
    case InternalFormat::RGB16F:
        return GL_RGB16F;
    case InternalFormat::RGB32F:
        return GL_RGB32F;
    case InternalFormat::RGBA:
        return GL_RGBA;
    case InternalFormat::RGBA16F:
        return GL_RGBA16F;
    case InternalFormat::RGBA32F:
        return GL_RGBA32F;
    default:
        break;
    }

    return GL_RGBA;
}

uint32 Texture::ToGLType(Type type)
{
    switch (type)
    {
    case Type::FLOAT:
        return GL_FLOAT;
    case Type::UNSIGNED_BYTE:
        return GL_UNSIGNED_BYTE;
    default:
        break;
    }

    return GL_FLOAT;
}

uint32 Texture::ToGLWrapping(Wrapping wrapping)
{
    switch (wrapping)
    {
    case Wrapping::CLAMP_TO_EDGE:
        return GL_CLAMP_TO_EDGE;
    case Wrapping::REPEAT:
        return GL_REPEAT;
    default:
        break;
    }

    return GL_CLAMP_TO_EDGE;
}
} // namespace spy
