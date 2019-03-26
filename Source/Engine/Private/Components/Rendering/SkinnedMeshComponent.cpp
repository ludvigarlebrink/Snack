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

#ifdef SPY_EDITOR
void SkinnedMeshComponent::OnEditorInspector()
{
}
#endif
} // namespace spy
