#include "SketchDragDrop.hpp"
#include "imgui/imgui.h"

namespace spy
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
} // namespace spy
