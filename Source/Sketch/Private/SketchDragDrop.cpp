#include "SketchDragDrop.hpp"
#include "imgui/imgui.h"

namespace snack
{
bool SketchDragDrop::AcceptPayload(const std::string& type, SketchDragDrop::Payload& payload)
{
    if (const ImGuiPayload* imPayload = ImGui::AcceptDragDropPayload(type.c_str()))
    {
        payload.data = imPayload->Data;
        payload.size = static_cast<uint64>(imPayload->DataSize);
        return true;
    }

    return false;
}

bool SketchDragDrop::BeginSource()
{
    return ImGui::BeginDragDropSource();
}

bool SketchDragDrop::BeginSource(const std::string& label)
{
    if (ImGui::BeginDragDropSource())
    {
        ImGui::Text(label.c_str());
        return true;
    }

    return false;
}

bool SketchDragDrop::BeginTarget()
{
    return ImGui::BeginDragDropTarget();
}

void SketchDragDrop::EndSource()
{
    ImGui::EndDragDropSource();
}

void SketchDragDrop::EndTarget()
{
    ImGui::EndDragDropTarget();
}

void SketchDragDrop::SetPayload(const std::string& type, void* data)
{
    ImGui::SetDragDropPayload(type.c_str(), data, sizeof(void*));
}

void SketchDragDrop::SetPayload(const std::string& type, void* data, uint64 size)
{
    ImGui::SetDragDropPayload(type.c_str(), data, size);
}

bool SketchDragDrop::TextSource(const std::string& label, const std::string& type, const std::string& data)
{
    if (ImGui::BeginDragDropSource())
    {
        ImGui::Text(label.c_str());
        ImGui::SetDragDropPayload(type.c_str(), data.data(), data.size() + 1);
        ImGui::EndDragDropSource();
        return true;
    }

    return false;
}

bool SketchDragDrop::TextTarget(const std::string& type, std::string& data)
{
    if (ImGui::BeginDragDropTarget())
    {
        bool returnVal = false;
        SketchDragDrop::Payload payload;
        if (SketchDragDrop::AcceptPayload(type, payload))
        {
            data = static_cast<char*>(payload.data);
            returnVal = true;
        }
        ImGui::EndDragDropTarget();
        return returnVal;
    }

    return false;
}
} // namespace snack
