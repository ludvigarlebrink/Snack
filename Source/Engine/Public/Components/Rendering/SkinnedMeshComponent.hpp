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

    void SetMaterial(Material* material);

    void SetMaterial(std::string path);

#ifdef SPY_EDITOR
    void OnEditorInspector() override;
#endif

private:
    
    Material* m_material;
};
} // namespace snack
