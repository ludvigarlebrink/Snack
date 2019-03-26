#pragma once

#define BEHAVIOR_BODY(behavior) \
public: \
    behavior(Transform* pTransform) \
        : BehaviorComponent(pTransform) \
    { \
    } \
    virtual ~behavior() \
    { \
    } \
    std::string GetComponentID() override \
    { \
        return typeid(behavior)\
    } \
private:

#include "BaseTypes.hpp"
#include "Components/BaseComponent.hpp"
#include "Transform.hpp"

namespace spy
{
class BehaviorSystem;

class ENGINE_API BehaviorComponent : public BaseComponent
{
    friend BehaviorSystem;

public:

    BehaviorComponent(Transform* transform);

    virtual ~BehaviorComponent();

    template <typename T>
    T* AddComponent();

    template <typename T>
    T* GetComponent();

    void OnEditorInspector() override;

protected:

    static void Destroy(Transform* transform);

    static Transform* Instantiate();

    static Transform* Instantiate(Transform* parent);

    virtual void OnAwake();

    virtual void OnDestroy();

    virtual void OnFixedTick(f32 fixedDeltaTime);

    virtual void OnPostTick(f32 deltaTime);
    
    virtual void OnPreTick(f32 deltaTime);

    virtual void OnStart();

    virtual void OnTick(f32 deltaTime);

private:

    static BehaviorSystem* m_behaviorSystem;
};

template<typename T>
T* BehaviorComponent::AddComponent()
{
    return GetTransform()->AddComponent<T>();
}

template<typename T>
T* BehaviorComponent::GetComponent()
{
    return GetTransform()->GetComponent<T>();
}
} // namespace spy
