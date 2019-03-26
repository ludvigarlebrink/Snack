#include "Components\Rendering\MeshComponent.hpp"
#include "Manager.hpp"
#include "Mathf.hpp"
#include "Transform.hpp"
#ifdef SPY_EDITOR
#include "SketchInclude.hpp"
#endif

namespace spy
{
MeshComponent::MeshComponent(Transform* transform)
    : BaseComponent(transform)
    , m_sphereRadius(0.0f)
    , m_aabbMax(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_aabbMin(glm::vec3(0.0f, 0.0f, 0.0f))
{
    Manager::Render()->RegisterMeshComponent(this);

    // @todo Hack!
    Vertex vertices[24];

    vertices[0].position = glm::vec3(-0.5f, 0.5f, 0.5f);
    vertices[1].position = glm::vec3(-0.5f, -0.5f, 0.5f);
    vertices[2].position = glm::vec3(0.5f, -0.5f, 0.5f);
    vertices[3].position = glm::vec3(0.5f, 0.5f, 0.5f);

    vertices[4].position = glm::vec3(0.5f, 0.5f, -0.5f);
    vertices[5].position = glm::vec3(0.5f, -0.5f, -0.5f);
    vertices[6].position = glm::vec3(-0.5f, -0.5f, -0.5f);
    vertices[7].position = glm::vec3(-0.5f, 0.5f, -0.5f);

    vertices[8].position = glm::vec3(0.5f, 0.5f, 0.5f);
    vertices[9].position = glm::vec3(0.5f, 0.5f, -0.5f);
    vertices[10].position = glm::vec3(-0.5f, 0.5f, -0.5f);
    vertices[11].position = glm::vec3(-0.5f, 0.5f, 0.5f);
    
    vertices[12].position = glm::vec3(-0.5f, -0.5f, 0.5f);
    vertices[13].position = glm::vec3(-0.5f, -0.5f, -0.5f);
    vertices[14].position = glm::vec3(0.5f, -0.5f, -0.5f);
    vertices[15].position = glm::vec3(0.5f, -0.5f, 0.5f);

    vertices[16].position = glm::vec3(0.5f, 0.5f, 0.5f);
    vertices[17].position = glm::vec3(0.5f, -0.5f, 0.5f);
    vertices[18].position = glm::vec3(0.5f, -0.5f, -0.5f);
    vertices[19].position = glm::vec3(0.5f, 0.5f, -0.5f);

    vertices[20].position = glm::vec3(-0.5f, 0.5f, -0.5f);
    vertices[21].position = glm::vec3(-0.5f, -0.5f, -0.5f);
    vertices[22].position = glm::vec3(-0.5f, -0.5f, 0.5f);
    vertices[23].position = glm::vec3(-0.5f, 0.5f, 0.5f);

    vertices[0].normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices[1].normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices[2].normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices[3].normal = glm::vec3(0.0f, 0.0f, 1.0f);

    vertices[4].normal = glm::vec3(0.0f, 0.0f, -1.0f);
    vertices[5].normal = glm::vec3(0.0f, 0.0f, -1.0f);
    vertices[6].normal = glm::vec3(0.0f, 0.0f, -1.0f);
    vertices[7].normal = glm::vec3(0.0f, 0.0f, -1.0f);

    vertices[8].normal = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[9].normal = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[10].normal = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[11].normal = glm::vec3(0.0f, 1.0f, 0.0f);

    vertices[12].normal = glm::vec3(0.0f, -1.0f, 0.0f);
    vertices[13].normal = glm::vec3(0.0f, -1.0f, 0.0f);
    vertices[14].normal = glm::vec3(0.0f, -1.0f, 0.0f);
    vertices[15].normal = glm::vec3(0.0f, -1.0f, 0.0f);

    vertices[16].normal = glm::vec3(1.0f, 0.0f, 0.0f);
    vertices[17].normal = glm::vec3(1.0f, 0.0f, 0.0f);
    vertices[18].normal = glm::vec3(1.0f, 0.0f, 0.0f);
    vertices[19].normal = glm::vec3(1.0f, 0.0f, 0.0f);

    vertices[20].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
    vertices[21].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
    vertices[22].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
    vertices[23].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

    vertices[0].tangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[1].tangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[2].tangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[3].tangent = glm::vec3(0.0f, 1.0f, 0.0f);

    vertices[4].tangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[5].tangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[6].tangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[7].tangent = glm::vec3(0.0f, 1.0f, 0.0f);

    vertices[8].tangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[9].tangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[10].tangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[11].tangent = glm::vec3(0.0f, 1.0f, 0.0f);

    vertices[0].textureCoordinates = glm::vec2(0.0f, 1.0f);
    vertices[1].textureCoordinates = glm::vec2(0.0f, 1.0f);
    vertices[2].textureCoordinates = glm::vec2(0.0f, 1.0f);
    vertices[3].textureCoordinates = glm::vec2(0.0f, 1.0f);

    vertices[4].textureCoordinates = glm::vec2(0.0f, 1.0f);
    vertices[5].textureCoordinates = glm::vec2(0.0f, 1.0f);
    vertices[6].textureCoordinates = glm::vec2(0.0f, 1.0f);
    vertices[7].textureCoordinates = glm::vec2(0.0f, 1.0f);

    vertices[8].textureCoordinates = glm::vec2(0.0f, 1.0f);
    vertices[9].textureCoordinates = glm::vec2(0.0f, 1.0f);
    vertices[10].textureCoordinates = glm::vec2(0.0f, 1.0f);
    vertices[11].textureCoordinates = glm::vec2(0.0f, 1.0f);

    uint32 elements[36] = {
        0u,
        1u,
        2u,
        2u,
        3u,
        0u,

        4u,
        5u,
        6u,
        6u,
        7u,
        4u,

        8u,
        9u,
        10u,
        10u,
        11u,
        8u,

        12u,
        13u,
        14u,
        14u,
        15u,
        12u,

        16u,
        17u,
        18u,
        18u,
        19u,
        16u,

        20u,
        21u,
        22u,
        22u,
        23u,
        20u
    };

    m_mesh = new Mesh();
    m_mesh->SetData(vertices, 24, sizeof(Vertex), elements, 36, Mesh::Optimization::STATIC_DRAW);
    int32 offset = 0;

    // Position.
    m_mesh->SetAttribPtr(0, Mesh::Type::VEC3, offset);
    offset += sizeof(glm::vec3);

    // Normal.
    m_mesh->SetAttribPtr(1, Mesh::Type::VEC3, offset);
    offset += sizeof(glm::vec3);

    // Tangent.
    m_mesh->SetAttribPtr(2, Mesh::Type::VEC3, offset);
    offset += sizeof(glm::vec3);

    // Texture coordinates.
    m_mesh->SetAttribPtr(3, Mesh::Type::VEC2, offset);

    m_mesh->EnableAttribute(0);
    m_mesh->EnableAttribute(1);
    m_mesh->EnableAttribute(2);
    m_mesh->EnableAttribute(3);

    m_sphereRadius = glm::length(glm::vec3(0.5f, 0.5f, 0.5f));
    m_aabbMax = glm::vec3(0.5f, 0.5f, 0.5f);
    m_aabbMin = glm::vec3(-0.5f, -0.5f, -0.5f);
}

MeshComponent::~MeshComponent()
{
    // @todo Hack! 
    delete m_mesh;
    Manager::Render()->DeregisterMeshComponent(this);
}

std::string MeshComponent::GetComponentID()
{
    return typeid(MeshComponent).name();
}

Mesh* MeshComponent::GetMesh() const
{
    return m_mesh;
}

f32 MeshComponent::GetSphereRadius() const
{
    glm::vec3 scale = GetTransform()->GetScale();
    f32 maxScale = Mathf::Max(scale.x, scale.y);
    maxScale = Mathf::Max(maxScale, scale.z);
    return m_sphereRadius * maxScale;
}

#ifdef SPY_EDITOR
void MeshComponent::OnEditorGizmo()
{
    glm::mat4 modelMatrix = GetTransform()->GetWorldMatrix();

    glm::vec3 p0 = modelMatrix * glm::vec4(m_aabbMin.x, m_aabbMin.y, m_aabbMin.z, 1.0f);
    glm::vec3 p1 = modelMatrix * glm::vec4(m_aabbMax.x, m_aabbMin.y, m_aabbMin.z, 1.0f);
    glm::vec3 p2 = modelMatrix * glm::vec4(m_aabbMax.x, m_aabbMin.y, m_aabbMax.z, 1.0f);
    glm::vec3 p3 = modelMatrix * glm::vec4(m_aabbMin.x, m_aabbMin.y, m_aabbMax.z, 1.0f);

    glm::vec3 p4 = modelMatrix * glm::vec4(m_aabbMin.x, m_aabbMax.y, m_aabbMin.z, 1.0f);
    glm::vec3 p5 = modelMatrix * glm::vec4(m_aabbMax.x, m_aabbMax.y, m_aabbMin.z, 1.0f);
    glm::vec3 p6 = modelMatrix * glm::vec4(m_aabbMax.x, m_aabbMax.y, m_aabbMax.z, 1.0f);
    glm::vec3 p7 = modelMatrix * glm::vec4(m_aabbMin.x, m_aabbMax.y, m_aabbMax.z, 1.0f);

    glm::vec3 p8 = modelMatrix * glm::vec4(m_aabbMin.x, m_aabbMin.y, m_aabbMin.z, 1.0f);
    glm::vec3 p9 = modelMatrix * glm::vec4(m_aabbMin.x, m_aabbMax.y, m_aabbMin.z, 1.0f);
    glm::vec3 p10 = modelMatrix * glm::vec4(m_aabbMax.x, m_aabbMin.y, m_aabbMin.z, 1.0f);
    glm::vec3 p11 = modelMatrix * glm::vec4(m_aabbMax.x, m_aabbMax.y, m_aabbMin.z, 1.0f);
    glm::vec3 p12 = modelMatrix * glm::vec4(m_aabbMin.x, m_aabbMin.y, m_aabbMax.z, 1.0f);
    glm::vec3 p13 = modelMatrix * glm::vec4(m_aabbMin.x, m_aabbMax.y, m_aabbMax.z, 1.0f);
    glm::vec3 p14 = modelMatrix * glm::vec4(m_aabbMax.x, m_aabbMin.y, m_aabbMax.z, 1.0f);
    glm::vec3 p15 = modelMatrix * glm::vec4(m_aabbMax.x, m_aabbMax.y, m_aabbMax.z, 1.0f);

    SketchGizmo::Line(p0, p1, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::Line(p1, p2, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::Line(p2, p3, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::Line(p3, p0, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

    SketchGizmo::Line(p4, p5, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::Line(p5, p6, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::Line(p6, p7, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::Line(p7, p4, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

    SketchGizmo::Line(p8, p9, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::Line(p10, p11, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::Line(p12, p13, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::Line(p14, p15, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
}

void MeshComponent::OnEditorInspector()
{

}
#endif
} // namespace spy
