#include "Sketch.hpp"
#include "RenderCoreInclude.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"

namespace spy
{
bool Sketch::Button(const std::string& label)
{
    return ImGui::Button(label.c_str());
}

bool Sketch::Checkbox(const std::string& label, bool& value)
{
    return ImGui::Checkbox(label.c_str(), &value);
}

bool Sketch::CollapsingHeader(const std::string& label)
{
    return ImGui::CollapsingHeader(label.c_str());
}

bool Sketch::FloatField(const std::string& label, f32& value)
{
    return ImGui::DragFloat(label.c_str(), &value, 0.01f);
}

bool Sketch::FloatField(const std::string& label, f32& value, f32 width)
{
    ImGui::PushItemWidth(width);
    bool returnVal = ImGui::DragFloat(label.c_str(), &value, 0.01f);
    ImGui::PopItemWidth();
    return returnVal;
}

void Sketch::Text(const std::string& text)
{
    ImGui::Text(text.c_str());
}

bool Sketch::Selectable(const std::string& label)
{
    return ImGui::Selectable(label.c_str());
}

bool Sketch::Selectable(const std::string& label, bool isSelected)
{
    return ImGui::Selectable(label.c_str(), isSelected);
}

void Sketch::SameLine()
{
    ImGui::SameLine();
}

void Sketch::Seperator()
{
    ImGui::Separator();
}

bool Sketch::TextField(const std::string& label, std::string& text)
{
    return ImGui::InputText(label.c_str(), &text);
}

void Sketch::Image(Texture* texture, const glm::vec2& size)
{
    ImGui::Image(static_cast<ImTextureID>(texture), ImVec2(size.x, size.y), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
}

bool Sketch::Vec2Field(const std::string& label, glm::vec2& value)
{
    f32 v[2] = { value.x, value.y };
    if (ImGui::DragFloat2(label.c_str(), v, 0.01f))
    {
        value.x = v[0];
        value.y = v[1];
        return true;
    }
    return false;
}

bool Sketch::Vec3Field(const std::string& label, glm::vec3& value)
{
    f32 v[3] = { value.x, value.y, value.z };
    if (ImGui::DragFloat3(label.c_str(), v, 0.01f))
    {
        value.x = v[0];
        value.y = v[1];
        value.z = v[2];
        return true;
    }
    return false;
}

bool Sketch::Vec4Field(const std::string& label, glm::vec4& value)
{
    f32 v[4] = { value.x, value.y, value.z, value.w };
    if (ImGui::DragFloat3(label.c_str(), v, 0.01f))
    {
        value.x = v[0];
        value.y = v[1];
        value.z = v[2];
        value.w = v[3];
        return true;
    }
    return false;
}
} // namespace spy
