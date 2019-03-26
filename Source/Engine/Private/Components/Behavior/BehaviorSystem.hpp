#pragma once

#include "BaseTypes.hpp"

#include <vector>

namespace spy
{
class BehaviorComponent;
class Transform;

class BehaviorSystem final
{
public:

    BehaviorSystem();

    ~BehaviorSystem();

    void DeregisterBehavior(BehaviorComponent* pBehavior);

    void FixedTick(f32 fixedDeltaTime);

    void OnPostTick(f32 deltaTime);

    void PreTick(f32 deltaTime);

    void Tick(f32 deltaTime);

    void RegisterBehavior(BehaviorComponent* pBehavior);

private:

    void SetUp();

    void TearDown();

private:

    std::vector<BehaviorComponent*> m_behaviors;
};
}
