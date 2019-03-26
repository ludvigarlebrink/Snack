#include "SketchTree.hpp"
#include "imgui/imgui.h"

namespace spy
{
bool SketchTree::BeginNode(const std::string& label, bool isSelected, bool& isClicked)
{
    uint32 flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
    if (isSelected)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }
    bool isOpen = ImGui::TreeNodeEx(label.c_str(), flags);
    isClicked = ImGui::IsItemClicked(0);
    return isOpen;
}

bool SketchTree::BeginNode(const std::string& label, uint64 id, bool isSelected, bool& isClicked)
{
    uint32 flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
    if (isSelected)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }
    bool isOpen = ImGui::TreeNodeEx((label + "###" + std::to_string(id)).c_str(), flags);
    isClicked = ImGui::IsItemClicked(0);
    return isOpen;
}

void SketchTree::EndNode()
{
    ImGui::TreePop();
}

bool SketchTree::LeafNode(const std::string& label, bool isSelected, bool& isClicked)
{
    uint32 flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_OpenOnArrow;
    if (isSelected)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }
    bool isOpen = ImGui::TreeNodeEx(label.c_str(), flags);
    isClicked = ImGui::IsItemClicked(0);
    return isOpen;
}

bool SketchTree::LeafNode(const std::string& label, uint64 id, bool isSelected, bool& isClicked)
{
    uint32 flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_OpenOnArrow;
    if (isSelected)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }
    bool isOpen = ImGui::TreeNodeEx((label + "###" + std::to_string(id)).c_str(), flags);
    isClicked = ImGui::IsItemClicked(0);
    return isOpen;
}
} // namespace spy
