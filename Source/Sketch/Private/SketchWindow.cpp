#include "SketchWindow.hpp"
#include "imgui/imgui.h"

namespace spy
{
void SketchWindow::BaseDockSpace()
{
    uint32 flags = ImGuiWindowFlags_MenuBar;
    flags |= ImGuiWindowFlags_NoDocking;
    flags |= ImGuiWindowFlags_NoTitleBar;
    flags |= ImGuiWindowFlags_NoCollapse;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    flags |= ImGuiWindowFlags_NoNavFocus;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    bool isOpen = true;
    ImGui::Begin("MainDockSpaceWindow", &isOpen, flags);

    ImGui::PopStyleVar(3);

    ImGuiID dockspaceID = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), 0);
    ImGui::End();
}

bool SketchWindow::Begin(const std::string& name)
{
    return ImGui::Begin(name.c_str());
}

bool SketchWindow::BeginChild(const std::string& id)
{
    return ImGui::BeginChild(id.c_str());
}

bool SketchWindow::BeginChild(const std::string& id, bool hasBorder)
{
    return ImGui::BeginChild(id.c_str(), ImVec2(0.0f, 0.0f), hasBorder);
}

bool SketchWindow::BeginChild(const std::string& id, const glm::vec2& size)
{
    return ImGui::BeginChild(id.c_str(), ImVec2(200.0f, size.y), true);
}

bool SketchWindow::BeginChild(const std::string& id, const glm::vec2& size, bool hasBorder)
{
    return ImGui::BeginChild(id.c_str(), ImVec2(size.x, size.y), hasBorder);
}

void SketchWindow::End()
{
    ImGui::End();
}

void SketchWindow::EndChild()
{
    ImGui::EndChild();
}

glm::vec2 SketchWindow::GetPosition()
{
    ImVec2 position = ImGui::GetWindowPos();
    return glm::vec2(position.x, position.y);
}

glm::vec2 SketchWindow::GetSize()
{
    return glm::vec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
}
} // namespace spy
