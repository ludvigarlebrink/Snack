#include "SketchMenu.hpp"
#include "imgui/imgui.h"

namespace snack
{
bool SketchMenu::Begin(const std::string& title)
{
    return ImGui::BeginMenu(title.c_str());
}

bool SketchMenu::BeginMain()
{
    return ImGui::BeginMainMenuBar();
}

void SketchMenu::End()
{
    ImGui::EndMenu();
}

void SketchMenu::EndMain()
{
    ImGui::EndMainMenuBar();
}

bool SketchMenu::Item(const std::string& label)
{
    return ImGui::MenuItem(label.c_str());
}

bool SketchMenu::Item(const std::string& label, bool enabled)
{
    return ImGui::MenuItem(label.c_str(), NULL, false, enabled);
}

bool SketchMenu::Item(const std::string& label, const std::string& shortcut)
{
    return ImGui::MenuItem(label.c_str(), shortcut.c_str());
}
} // namespace snack
