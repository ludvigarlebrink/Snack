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

void SketchGizmo::Cube(const glm::mat4& model)
{
    Cube(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void SketchGizmo::Cube(const glm::mat4& model, const glm::vec4& color)
{
    SketchInternal::Vertex vertices[24];

    // Plane 1.
    vertices[0].position = model * glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);
    vertices[1].position = model * glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);
    vertices[2].position = model * glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);
    vertices[3].position = model * glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

    // Plane 2.
    vertices[4].position = model * glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);
    vertices[5].position = model * glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);
    vertices[6].position = model * glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);
    vertices[7].position = model * glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);

    // Plane 3.
    vertices[8].position = model * glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    vertices[9].position = model * glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);
    vertices[10].position = model * glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);
    vertices[11].position = model * glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);

    // Plane 4.
    vertices[12].position = model * glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);
    vertices[13].position = model * glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);
    vertices[14].position = model * glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);
    vertices[15].position = model * glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);

    // Plane 5.
    vertices[16].position = model * glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    vertices[17].position = model * glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);
    vertices[18].position = model * glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);
    vertices[19].position = model * glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);

    // Plane 6.
    vertices[20].position = model * glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);
    vertices[21].position = model * glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);
    vertices[22].position = model * glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);
    vertices[23].position = model * glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);

    // Color.
    vertices[0].position = color;
    vertices[1].position = color;
    vertices[2].position = color;
    vertices[3].position = color;
    vertices[4].position = color;
    vertices[5].position = color;
    vertices[6].position = color;
    vertices[7].position = color;
    vertices[8].position = color;
    vertices[9].position = color;
    vertices[10].position = color;
    vertices[11].position = color;
    vertices[12].position = color;
    vertices[13].position = color;
    vertices[14].position = color;
    vertices[15].position = color;
    vertices[16].position = color;
    vertices[17].position = color;
    vertices[18].position = color;
    vertices[19].position = color;
    vertices[20].position = color;
    vertices[21].position = color;
    vertices[22].position = color;
    vertices[23].position = color;

    uint32 element = SketchInternal::m_gizmoDrawData.vertices.size();

    // Plane 1.
    SketchInternal::m_gizmoDrawData.elements.push_back(element);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 1u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 3u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element);

    // Plane 2.
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 4u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 5u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 6u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 6u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 7u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 4u);

    // Plane 3.
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 8u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 9u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 10u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 10u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 11u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 8u);

    // Plane 4.
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 12u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 13u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 14u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 14u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 15u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 12u);

    // Plane 5.
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 16u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 17u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 18u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 18u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 19u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 16u);

    // Plane 6.
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 20u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 21u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 22u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 22u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 23u);
    SketchInternal::m_gizmoDrawData.elements.push_back(element + 20u);

    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[0]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[1]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[2]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[3]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[4]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[5]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[6]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[7]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[8]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[9]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[10]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[11]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[12]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[13]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[14]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[15]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[16]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[17]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[18]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[19]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[20]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[21]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[22]);
    SketchInternal::m_gizmoDrawData.vertices.push_back(vertices[23]);
}

void SketchGizmo::CubeOverdrawn(const glm::mat4& model)
{
    CubeOverdrawn(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void SketchGizmo::CubeOverdrawn(const glm::mat4& model, const glm::vec4& color)
{
    SketchInternal::Vertex vertices[24];

    // Plane 1.
    vertices[0].position = model * glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);
    vertices[1].position = model * glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    vertices[2].position = model * glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);
    vertices[3].position = model * glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);

    // Plane 2.
    vertices[4].position = model * glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);
    vertices[5].position = model * glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);
    vertices[6].position = model * glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);
    vertices[7].position = model * glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);

    // Plane 3.
    vertices[8].position = model * glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);
    vertices[9].position = model * glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    vertices[10].position = model * glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);
    vertices[11].position = model * glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);

    // Plane 4.
    vertices[12].position = model * glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);
    vertices[13].position = model * glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);
    vertices[14].position = model * glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);
    vertices[15].position = model * glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);

    // Plane 5.
    vertices[16].position = model * glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);
    vertices[17].position = model * glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    vertices[18].position = model * glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);
    vertices[19].position = model * glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);

    // Plane 6.
    vertices[20].position = model * glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);
    vertices[21].position = model * glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);
    vertices[22].position = model * glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);
    vertices[23].position = model * glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);

    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    vertices[4].color = color;
    vertices[5].color = color;
    vertices[6].color = color;
    vertices[7].color = color;
    vertices[8].color = color;
    vertices[9].color = color;
    vertices[10].color = color;
    vertices[11].color = color;
    vertices[12].color = color;
    vertices[13].color = color;
    vertices[14].color = color;
    vertices[15].color = color;
    vertices[16].color = color;
    vertices[17].color = color;
    vertices[18].color = color;
    vertices[19].color = color;
    vertices[20].color = color;
    vertices[21].color = color;
    vertices[22].color = color;
    vertices[23].color = color;

    uint32 element = SketchInternal::m_gizmoDrawData.verticesOverdrawn.size();

    // Plane 1.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 1u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 2u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 3u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element);

    // Plane 2.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 4u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 5u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 6u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 6u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 7u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 4u);

    // Plane 3.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 8u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 9u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 10u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 10u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 11u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 8u);

    // Plane 4.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 12u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 13u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 14u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 14u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 15u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 12u);

    // Plane 5.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 16u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 17u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 18u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 18u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 19u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 16u);

    // Plane 6.
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 20u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 21u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 22u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 22u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 23u);
    SketchInternal::m_gizmoDrawData.elementsOverdrawn.push_back(element + 20u);

    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[0]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[1]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[2]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[3]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[4]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[5]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[6]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[7]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[8]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[9]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[10]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[11]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[12]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[13]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[14]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[15]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[16]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[17]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[18]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[19]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[20]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[21]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[22]);
    SketchInternal::m_gizmoDrawData.verticesOverdrawn.push_back(vertices[23]);
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
