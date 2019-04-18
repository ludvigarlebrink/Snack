#pragma once

#include "BaseTypes.hpp"
#include "RenderCoreForward.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace snack
{
class SKETCH_API Sketch
{
public:

    enum class Font : uint32
    {
        FONT0,
        FONT1
    };

public:

    static bool Button(const std::string& label);

    static bool Checkbox(const std::string& label, bool& value);

    static bool CollapsingHeader(const std::string& label);

    static bool CollapsingHeader(const std::string& label, bool& isOpen);

    static bool FloatField(const std::string& label, f32& value);

    static bool FloatField(const std::string& label, f32& value, f32 width);

    static void Image(Texture* texture, const glm::vec2& size);

    static bool ImageButton(Texture* texture, bool flip);

    static bool ImageButton(Texture* texture, bool flip, const glm::vec4& color);

    static void Indent();

    static bool IntField(const std::string& label, int32& value);

    static void ResetFont();

    static bool Selectable(const std::string& label);

    static bool Selectable(const std::string& label, bool isSelected);

    static void SameLine();

    static void Seperator();

    static void SetFont(Font font);

    static void Text(const std::string& text);

    static bool TextField(const std::string& label, std::string& text);
 
    static void Unindent();

    static bool Vec2Field(const std::string& label, glm::vec2& value);

    static bool Vec3Field(const std::string& label, glm::vec3& value);

    static bool Vec4Field(const std::string& label, glm::vec4& value);
};
} // namespace snack
