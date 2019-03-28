#include "SketchGizmo.hpp"
#include "SketchInternal.hpp"

namespace spy
{
void SketchGizmo::Cone(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& rightAxis, f32 baseScaling, f32 topScaling)
{
    Cone(origin, direction, rightAxis, baseScaling, topScaling, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void SketchGizmo::Cone(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& rightAxis, f32 baseScaling, f32 topScaling, const glm::vec4& color)
{
    glm::vec3 forward = glm::cross(direction , rightAxis);

    SketchInternal::Vertex vertices[5];
    vertices[0].position = origin + direction * topScaling;
    vertices[1].position = origin + rightAxis * 0.5f * baseScaling + forward * 0.5f * baseScaling;
    vertices[2].position = origin + rightAxis * 0.5f * baseScaling - forward * 0.5f * baseScaling;
    vertices[3].position = origin - rightAxis * 0.5f * baseScaling - forward * 0.5f * baseScaling;
    vertices[4].position = origin - rightAxis * 0.5f * baseScaling + forward * 0.5f * baseScaling;

    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    vertices[4].color = color;

    uint32 element = SketchInternal::m_gizmoDrawData.vertices.size();

    // Triangle 1.
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 1u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 3u);

    // Triangle 2.
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 3u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 4u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 1u);

    // // Triangle 3.
    SketchInternal::m_gizmoDrawData.elements.push_back(element);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 1u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 2u);

    // // Triangle 4.
    SketchInternal::m_gizmoDrawData.elements.push_back(element);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 3u);

    // // Triangle 5.
    SketchInternal::m_gizmoDrawData.elements.push_back(element);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 3u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 4u);

    // Triangle 6.
    SketchInternal::m_gizmoDrawData.elements.push_back(element);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 4u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 1u);

    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[0]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[1]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[2]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[3]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[4]);
}

void SketchGizmo::ConeOverdrawn(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& rightAxis, f32 baseScaling, f32 topScaling)
{
    ConeOverdrawn(origin, direction, rightAxis, baseScaling, topScaling, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void SketchGizmo::ConeOverdrawn(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& rightAxis, f32 baseScaling, f32 topScaling, const glm::vec4& color)
{
    glm::vec3 forward = glm::cross(direction, rightAxis);

    SketchInternal::Vertex vertices[5];
    vertices[0].position = origin + direction * topScaling;
    vertices[1].position = origin + rightAxis * 0.5f * baseScaling + forward * 0.5f * baseScaling;
    vertices[2].position = origin + rightAxis * 0.5f * baseScaling - forward * 0.5f * baseScaling;
    vertices[3].position = origin - rightAxis * 0.5f * baseScaling - forward * 0.5f * baseScaling;
    vertices[4].position = origin - rightAxis * 0.5f * baseScaling + forward * 0.5f * baseScaling;

    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    vertices[4].color = color;

    uint32 element = SketchInternal::m_gizmoDrawData.verticesOverdrawn.size();

    // Triangle 1.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 1u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 3u);

    // Triangle 2.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 3u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 4u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 1u);

    // // Triangle 3.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 1u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 2u);

    // // Triangle 4.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 3u);

    // // Triangle 5.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 3u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 4u);

    // Triangle 6.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 4u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 1u);

    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[0]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[1]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[2]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[3]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[4]);
}

void SketchGizmo::Line(const glm::vec3& p0, glm::vec3& p1)
{
    Line(p0, p1, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void SketchGizmo::Line(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color)
{
    SketchInternal::Vertex line[2];
    line[0].position = p0;
    line[1].position = p1;
    
    line[0].color = color;
    line[1].color = color;

    uint32 lineElement = SketchInternal::m_gizmoDrawData.lines.size();
    SketchInternal::m_gizmoDrawData.lineElements.push_back(lineElement);
    SketchInternal::m_gizmoDrawData.lineElements.push_back(lineElement + 1u);
    SketchInternal::m_gizmoDrawData.lines.push_back(line[0]);
    SketchInternal::m_gizmoDrawData.lines.push_back(line[1]);
}

void SketchGizmo::LineOverdrawn(const glm::vec3& p0, glm::vec3& p1)
{
    LineOverdrawn(p0, p1, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void SketchGizmo::LineOverdrawn(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color)
{
    SketchInternal::Vertex line[2];
    line[0].position = p0;
    line[0].color = color;
    line[1].position = p1;
    line[1].color = color;

    int32 lineElement = SketchInternal::m_gizmoDrawData.linesOverdrawn.size();
    SketchInternal::m_gizmoDrawData.lineElementsOverdrawn.push_back(lineElement);
    SketchInternal::m_gizmoDrawData.lineElementsOverdrawn.push_back(lineElement + 1u);
    SketchInternal::m_gizmoDrawData.linesOverdrawn.push_back(line[0]);
    SketchInternal::m_gizmoDrawData.linesOverdrawn.push_back(line[1]);
}
void SketchGizmo::Quad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
{
    Quad(p0, p1, p2, p3, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void SketchGizmo::Quad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
{
    SketchInternal::Vertex vertices[4];
    vertices[0].position = p0;
    vertices[1].position = p1;
    vertices[2].position = p2;
    vertices[3].position = p3;

    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;

    uint32 element = SketchInternal::m_gizmoDrawData.vertices.size();

    // Triangle 1.
    SketchInternal::m_gizmoDrawData.elements.push_back(element);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 1u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 2u);

    // Triangle 2.
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 3u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element);

    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[0]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[1]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[2]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[3]);
}

void SketchGizmo::QuadOverdrawn(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
{
    QuadOverdrawn(p0, p1, p2, p3, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void SketchGizmo::QuadOverdrawn(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
{
    SketchInternal::Vertex vertices[4];
    vertices[0].position = p0;
    vertices[1].position = p1;
    vertices[2].position = p2;
    vertices[3].position = p3;

    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;

    uint32 element = SketchInternal::m_gizmoDrawData.verticesOverdrawn.size();

    // Triangle 1.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 1u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 2u);

    // Triangle 2.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 3u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element);

    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[0]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[1]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[2]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[3]);
}
} // namespace spy
