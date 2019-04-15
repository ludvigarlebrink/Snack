#pragma once

#include "Components/BaseComponent.hpp"
#include "Rendering/Material.hpp"

#include <glm/glm.hpp>

namespace snack
{
class SkinnedMeshComponent final : public BaseComponent
{
public:

    SkinnedMeshComponent(Transform* transform);

    ~SkinnedMeshComponent();

    std::string GetComponentID() override;

    Material* GetMaterial() const;

    void Load(cereal::JSONInputArchive& archive) override;

#ifdef SPY_EDITOR
    void OnEditorInspector() override;
#endif

    void Save(cereal::JSONOutputArchive& archive) override;

    void SetMaterial(Material* material);

    void SetMaterial(std::string path);

private:
    
    Material* m_material;
};
} // namespace snack
