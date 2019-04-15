#include "Components/Rendering/JointComponent.hpp"
#include "Manager.hpp"
#include "UtilsInclude.hpp"

namespace snack
{
JointComponent::JointComponent(Transform* transform)
    : BaseComponent(transform)
{
    Manager::Render()->RegisterJointComponent(this);
}

JointComponent::~JointComponent()
{
    Manager::Render()->DeregisterJointComponent(this);
}

std::string JointComponent::GetComponentID()
{
    return CLASS_NAME(JointComponent);
}

void JointComponent::Load(cereal::JSONInputArchive& archive)
{
    BaseComponent::Load(archive);
}

#ifdef SPY_EDITOR
void JointComponent::OnEditorInspector()
{
}

void JointComponent::Save(cereal::JSONOutputArchive& archive)
{
    BaseComponent::Save(archive);
}
} // namespace snack
#endif
