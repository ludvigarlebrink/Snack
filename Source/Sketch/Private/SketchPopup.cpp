#include "SketchPopup.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_stdlib.h"

namespace snack
{
bool SketchPopup::BeginContext(const std::string& id)
{
    return ImGui::BeginPopupContextItem(id.c_str());
}

bool SketchPopup::BeginContext(uint64 id)
{
    return ImGui::BeginPopupContextItem(std::to_string(id).c_str());
}

bool SketchPopup::BeginModal(const std::string& label)
{
    bool isOpen = true;
    return ImGui::BeginPopupModal(label.c_str(), &isOpen, ImGuiWindowFlags_NoDocking);
}

bool SketchPopup::BeginModal(const std::string& label, const glm::vec2& size)
{
    bool isOpen = true;
    ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
    return ImGui::BeginPopupModal(label.c_str(), &isOpen, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize);
}

void SketchPopup::Close()
{
    ImGui::CloseCurrentPopup();
}

void SketchPopup::End()
{
    ImGui::EndPopup();
}

bool SketchPopup::Dialog(const std::string& label, const std::string& description, const std::string& applyButtonLabel, const std::string& cancelButtonLabel, std::string& output)
{
    bool isOpen = true;
    bool returnVal = false;
    ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
    if (ImGui::BeginPopupModal(label.c_str(), &isOpen, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize))
    {
        ImGui::Text(description.c_str());

        ImGui::PushItemWidth(-1);
        if (ImGui::InputText("##label", &output, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            ImGui::ClosePopupToLevel(0, false);
            returnVal = true;
        }
        ImGui::PopItemWidth();

        if (ImGui::Button(applyButtonLabel.c_str()))
        {
            ImGui::ClosePopupToLevel(0, false);
            returnVal = true;
        }

        ImGui::SameLine();

        if (ImGui::Button(cancelButtonLabel.c_str()))
        {
            ImGui::ClosePopupToLevel(0, false);
            output.clear();
        }

        ImGui::EndPopup();
    }
    else if (!isOpen)
    {
        ImGui::ClosePopupToLevel(0, false);
        output.clear();
    }

    return returnVal;
}

bool SketchPopup::DialogYesNo(const std::string& label, const std::string& description)
{
    bool isOpen = true;
    bool returnVal = false;
    if (ImGui::BeginPopupModal(label.c_str(), &isOpen, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize))
    {
        ImGui::Text(description.c_str());

        if (ImGui::Button("Yes"))
        {
            ImGui::ClosePopupToLevel(0, false);
            returnVal = true;
        }

        ImGui::SameLine();

        if (ImGui::Button("No"))
        {
            ImGui::ClosePopupToLevel(0, false);
        }

        ImGui::EndPopup();
    }
    else if (!isOpen)
    {
        ImGui::ClosePopupToLevel(0, false);
    }

    return returnVal;
}

bool SketchPopup::MenuItemOpenPopup(const std::string& label, const std::string& popupLabel)
{
    ImGui::PushItemWidth(-1);
    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
    bool returnVal = false;
    if (ImGui::MenuItem(label.c_str()))
    {
        ImGui::OpenPopup(popupLabel.c_str());
        returnVal = true;
    }
    ImGui::PopItemFlag();
    ImGui::PopItemWidth();
    return returnVal;
}

void SketchPopup::OpenPopup(const std::string& label)
{
    ImGui::OpenPopup(label.c_str());
}
} // namespace snack
