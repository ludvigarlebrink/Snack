#include "Components\Rendering\SkinnedMeshComponent.hpp"
#include "Manager.hpp"
#include "UtilsInclude.hpp"

namespace snack
{
SkinnedMeshComponent::SkinnedMeshComponent(Transform* transform)
    : BaseComponent(transform)
{
    Manager::Render()->RegisterSkinnedMeshComponent(this);
}

SkinnedMeshComponent::~SkinnedMeshComponent()
{
    Manager::Render()->DeregisterSkinnedMeshComponent(this);
}

std::string SkinnedMeshComponent::GetComponentID()
{
    return CLASS_NAME(PointLightComponent);
}

Material* SkinnedMeshComponent::GetMaterial() const
{
    return m_material;
}

void SkinnedMeshComponent::Load(cereal::JSONInputArchive& archive)
{
    BaseComponent::Load(archive);
}

#ifdef SPY_EDITOR
void SkinnedMeshComponent::OnEditorInspector()
{
}
#endif

void SkinnedMeshComponent::Save(cereal::JSONOutputArchive& archive)
{
    BaseComponent::Save(archive);
}

void SkinnedMeshComponent::SetMaterial(Material* material)
{
    m_material = material;
}

void SkinnedMeshComponent::SetMaterial(std::string path)
{
    // TODO maybe?
}
} // namespace snack
