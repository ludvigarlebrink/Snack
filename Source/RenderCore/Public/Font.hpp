#pragma once

#include "BaseTypes.hpp"

#include <glm/glm.hpp>
#include <string>

namespace snack
{
class Texture;

class RENDER_CORE_API Font final
{
public:

    struct Character
    {
        glm::ivec2 size;
        glm::ivec2 bearing;
        glm::vec2 texturePosition;
        glm::vec2 textureSize;
        uint32 advance;
    };

public:

    Font();

    ~Font();

    void Bind(uint32 location);

    Character GetCharacter(uchar character) const;

    int32 GetFontSize() const;

    Texture* GetTexture() const;

    void LoadTTF(const std::string& filename, int32 fontSize);

private:

    void TearDown();

private:

    int32 m_fontSize;

    Character m_characters[128];
    Texture* m_texture;
};
} // namespace snack
