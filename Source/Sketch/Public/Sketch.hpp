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

    static bool Button(const std::string& label);

    static bool Checkbox(const std::string& label, bool& value);

    static bool CollapsingHeader(const std::string& label);

    static bool FloatField(const std::string& label, f32& value);

    static bool FloatField(const std::string& label, f32& value, f32 width);

    static void Image(Texture* texture, const glm::vec2& size);

    static bool ImageButton(Texture* texture, bool flip);

    static bool ImageButton(Texture* texture, bool flip, const glm::vec4& color);

    static bool IntField(const std::string& label, int32& value);

    static bool Selectable(const std::string& label);

    static bool Selectable(const std::string& label, bool isSelected);

    static void SameLine();

    static void Seperator();

    static void Text(const std::string& text);

    static bool TextField(const std::string& label, std::string& text);
 
    static bool Vec2Field(const std::string& label, glm::vec2& value);

    static bool Vec3Field(const std::string& label, glm::vec3& value);

    static bool Vec4Field(const std::string& label, glm::vec4& value);
};
} // namespace snack
