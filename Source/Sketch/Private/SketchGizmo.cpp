#include "SketchGizmo.hpp"
#include "SketchInternal.hpp"

namespace spy
{
void SketchGizmo::Line(const glm::vec3& p0, glm::vec3& p1)
{
    SketchInternal::LineVertex line[2];
    line[0].position = p0;
    line[0].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    line[1].position = p1;
    line[1].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    int32 lineElement = SketchInternal::m_gizmoDrawData.lines.size();
    SketchInternal::m_gizmoDrawData.lineElements.push_back(lineElement);
    SketchInternal::m_gizmoDrawData.lineElements.push_back(lineElement + 1);
    SketchInternal::m_gizmoDrawData.lines.push_back(line[0]);
    SketchInternal::m_gizmoDrawData.lines.push_back(line[1]);
}

void SketchGizmo::Line(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color)
{
    SketchInternal::LineVertex line[2];
    line[0].position = p0;
    line[0].color = color;
    line[1].position = p1;
    line[1].color = color;

    int32 lineElement = SketchInternal::m_gizmoDrawData.lines.size();
    SketchInternal::m_gizmoDrawData.lineElements.push_back(lineElement);
    SketchInternal::m_gizmoDrawData.lineElements.push_back(lineElement + 1);
    SketchInternal::m_gizmoDrawData.lines.push_back(line[0]);
    SketchInternal::m_gizmoDrawData.lines.push_back(line[1]);
}

void SketchGizmo::LineOverdrawn(const glm::vec3& p0, glm::vec3& p1)
{
    SketchInternal::LineVertex line[2];
    line[0].position = p0;
    line[0].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    line[1].position = p1;
    line[1].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    int32 lineElement = SketchInternal::m_gizmoDrawData.linesOverdrawn.size();
    SketchInternal::m_gizmoDrawData.lineElementsOverdrawn.push_back(lineElement);
    SketchInternal::m_gizmoDrawData.lineElementsOverdrawn.push_back(lineElement + 1);
    SketchInternal::m_gizmoDrawData.linesOverdrawn.push_back(line[0]);
    SketchInternal::m_gizmoDrawData.linesOverdrawn.push_back(line[1]);
}

void SketchGizmo::LineOverdrawn(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color)
{
    SketchInternal::LineVertex line[2];
    line[0].position = p0;
    line[0].color = color;
    line[1].position = p1;
    line[1].color = color;

    int32 lineElement = SketchInternal::m_gizmoDrawData.linesOverdrawn.size();
    SketchInternal::m_gizmoDrawData.lineElementsOverdrawn.push_back(lineElement);
    SketchInternal::m_gizmoDrawData.lineElementsOverdrawn.push_back(lineElement + 1);
    SketchInternal::m_gizmoDrawData.linesOverdrawn.push_back(line[0]);
    SketchInternal::m_gizmoDrawData.linesOverdrawn.push_back(line[1]);
}
} // namespace spy
