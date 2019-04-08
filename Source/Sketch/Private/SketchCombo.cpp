#include "SketchCombo.hpp"
#include "imgui/imgui.h"

namespace spy
{
bool SketchCombo::Begin(const std::string& label, const std::string& previewLabel)
{
    return ImGui::BeginCombo(label.c_str(), previewLabel.c_str());
}

bool SketchCombo::Begin(const std::string& title, const std::string& previewLabel, f32 width)
{
    // This code is a bit hacky.
    ImGui::PushItemWidth(width);
    bool returnVal = ImGui::BeginCombo(title.c_str(), previewLabel.c_str());

    // I do not really know why this works. But it will crash if this is removed.
    if (!returnVal)
    {
        ImGui::PopItemWidth();
    }

    return returnVal;
}

void SketchCombo::End()
{
    ImGui::EndCombo();
}

bool SketchCombo::Selectable(const std::string& label)
{
    return ImGui::Selectable(label.c_str());
}

bool SketchCombo::Selectable(const std::string& label, bool isSelected)
{
    return ImGui::Selectable(label.c_str(), isSelected);
}
} // namespace spy
