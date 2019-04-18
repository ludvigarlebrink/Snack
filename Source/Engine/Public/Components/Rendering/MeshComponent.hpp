#pragma once

#include "Components/BaseComponent.hpp"
#include "Mesh.hpp"
#include "Rendering/Material.hpp"

#include <glm/glm.hpp>

namespace snack
{
/**
 * @brief A mesh component.
 */
class MeshComponent final : public BaseComponent
{
public:

    MeshComponent(Transform* transform);

    ~MeshComponent();

    std::string GetComponentID() override;

    Material* GetMaterial() const;

    Mesh* GetMesh() const;

    f32 GetSphereRadius() const;

    void Load(cereal::JSONInputArchive& archive) override;

    void Save(cereal::JSONOutputArchive& archive) override;

    void SetMaterial(Material* material);

    void SetMaterial(const std::string& path);

#ifdef SPY_EDITOR
    void OnEditorGizmo() override;

    void OnEditorInspector() override;
#endif

private:

    Mesh* m_mesh;
    Material* m_material;
    std::string m_materialName;
    f32 m_sphereRadius;
    glm::vec3 m_aabbMax;
    glm::vec3 m_aabbMin;
};
} // namespace snack

/**
 * @class snack::MeshComponent
 * @ingroup Engine
 */
