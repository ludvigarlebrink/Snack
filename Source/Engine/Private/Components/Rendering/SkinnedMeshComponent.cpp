#include "Components\Rendering\SkinnedMeshComponent.hpp"
#include "Manager.hpp"

namespace spy
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
    return typeid(SkinnedMeshComponent).name();
}

Material* SkinnedMeshComponent::GetMaterial() const
{
    return m_material;
}

void SkinnedMeshComponent::SetMaterial(Material * material)
{
    m_material = material;
}

void SkinnedMeshComponent::SetMaterial(std::string path)
{
    // TODO maybe?
}

#ifdef SPY_EDITOR
void SkinnedMeshComponent::OnEditorInspector()
{
}
#endif
} // namespace spy
