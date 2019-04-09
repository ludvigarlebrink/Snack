#include "Components/Rendering/JointComponent.hpp"
#include "Manager.hpp"

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
    return typeid(JointComponent).name();
}

#ifdef SPY_EDITOR
void JointComponent::OnEditorInspector()
{
}
} // namespace snack
#endif
