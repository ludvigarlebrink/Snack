#include "Components/Behavior/BehaviorComponent.hpp"
#include "Transform.hpp"
#include "Manager.hpp"

namespace snack
{
BehaviorSystem* BehaviorComponent::m_behaviorSystem = nullptr;

BehaviorComponent::BehaviorComponent(Transform* transform)
    : BaseComponent(transform)
{
}

BehaviorComponent::~BehaviorComponent()
{
}

void BehaviorComponent::OnEditorInspector()
{
    BaseComponent::OnEditorInspector();
}

void BehaviorComponent::Destroy(Transform* transform)
{
    Manager::Scene()->Destroy(transform);
}

Transform* BehaviorComponent::Instantiate()
{
    return Manager::Scene()->Instantiate();
}

Transform* BehaviorComponent::Instantiate(Transform* parent)
{
    return Manager::Scene()->Instantiate(parent);
}

void BehaviorComponent::OnAwake()
{
    // Do nothing...
}

void BehaviorComponent::OnDestroy()
{
    // Do nothing...
}

void BehaviorComponent::OnFixedTick(f32 fixedDeltaTime)
{
    // Do nothing...
}

void BehaviorComponent::OnPostTick(f32 deltaTime)
{
    // Do nothing...
}

void BehaviorComponent::OnPreTick(f32 deltaTime)
{
    // Do nothing...
}

void BehaviorComponent::OnStart()
{
    // Do nothing...
}

void BehaviorComponent::OnTick(f32 deltaTime)
{
    // Do nothing...
}
} // namespace snack
