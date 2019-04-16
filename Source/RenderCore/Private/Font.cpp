#include "Font.hpp"
#include "Mathf.hpp"
#include "Texture.hpp"

#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace snack
{
Font::Font()
    : m_fontSize(12)
    , m_texture(nullptr)
{
}

Font::~Font()
{
}

void Font::Bind(uint32 location)
{
    m_texture->Bind(location);
}

Font::Character Font::GetCharacter(uchar character) const
{
    return m_characters[character];
}

int32 Font::GetFontSize() const
{
    return m_fontSize;
}

Texture* Font::GetTexture() const
{
    return m_texture;
}

void Font::LoadTTF(const std::string& filepath, int32 fontSize)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    FT_Face face;
    if (FT_New_Face(ft, filepath.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    m_fontSize = fontSize;

    FT_Set_Pixel_Sizes(face, 0, m_fontSize);

    int32 maxWidth = 0;
    uint32 verticalOffset = 0u;
    for (uchar c = 0u; c < 128u; ++c)
    {
        if (!FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            m_characters[c].size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
            m_characters[c].bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
            m_characters[c].advance = face->glyph->advance.x;

            if (maxWidth < face->glyph->bitmap.width)
            {
                maxWidth = face->glyph->bitmap.width;
            }
        }
    }

    uint32 textureSize = 0u;
    uint32 characterSize = 0u;

    // We will create a 12 * 12 grid of glyphs.
    if (maxWidth < fontSize)
    {
        textureSize = Mathf::UpperPowerOfTwo(static_cast<uint32>(fontSize * 12));
        characterSize = static_cast<uint32>(fontSize);
    }
    else
    {
        textureSize = Mathf::UpperPowerOfTwo(static_cast<uint32>(maxWidth * 12));
        characterSize = static_cast<uint32>(maxWidth);
    }

    m_texture = new Texture();
    m_texture->SetData(textureSize, textureSize, Texture::InternalFormat::R, Texture::Format::R, Texture::Type::UNSIGNED_BYTE, nullptr);

    // ...and we need to loop through all of the glyphs again.
    for (uchar c = 0u; c < 128u; ++c)
    {
        if (!FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            int32 x = (static_cast<int32>(c) % 12) * characterSize;
            int32 y = (static_cast<int32>(c) / 12) * characterSize;
            m_texture->SetSubData(x, y, face->glyph->bitmap.width, face->glyph->bitmap.rows, Texture::Format::R, face->glyph->bitmap.buffer);
            m_characters[c].texturePosition = glm::vec2(static_cast<f32>(x) / static_cast<f32>(textureSize), static_cast<f32>(y) / static_cast<f32>(textureSize));
            m_characters[c].textureSize = glm::vec2(static_cast<f32>(m_characters[c].size.x) / static_cast<f32>(textureSize), static_cast<f32>(m_characters[c].size.y) / static_cast<f32>(textureSize));
        }
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void Font::TearDown()
{
}
} // namespace snack
