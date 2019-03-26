#include "BehaviorSystem.hpp"
#include "Components/Behavior/BehaviorComponent.hpp"
#include "Transform.hpp"

namespace spy
{
BehaviorSystem::BehaviorSystem()
{
    SetUp();
}

BehaviorSystem::~BehaviorSystem()
{
    TearDown();
}

void BehaviorSystem::DeregisterBehavior(BehaviorComponent* transform)
{
    for (int32 i = 0; i < m_behaviors.size(); ++i)
    {
        if (m_behaviors[i] == transform)
        {
            m_behaviors.erase(m_behaviors.begin() + i);
            return;
        }
    }
}

void BehaviorSystem::FixedTick(f32 fixedDeltaTime)
{
    for (int32 i = 0; i < m_behaviors.size(); ++i)
    {
        m_behaviors[i]->OnFixedTick(fixedDeltaTime);
    }
}

void BehaviorSystem::OnPostTick(f32 deltaTime)
{
    for (int32 i = 0; i < m_behaviors.size(); ++i)
    {
        m_behaviors[i]->OnPostTick(deltaTime);
    }
}

void BehaviorSystem::PreTick(f32 deltaTime)
{
    for (int32 i = 0; i < m_behaviors.size(); ++i)
    {
        m_behaviors[i]->OnPreTick(deltaTime);
    }
}

void BehaviorSystem::Tick(f32 deltaTime)
{
    for (int32 i = 0; i < m_behaviors.size(); ++i)
    {
        m_behaviors[i]->OnTick(deltaTime);
    }
}

void BehaviorSystem::RegisterBehavior(BehaviorComponent* pBehavior)
{
    m_behaviors.push_back(pBehavior);
}

void BehaviorSystem::SetUp()
{
    BehaviorComponent::m_behaviorSystem = this;
}

void BehaviorSystem::TearDown()
{
    BehaviorComponent::m_behaviorSystem = nullptr;
}
} // namespace spy
