#pragma once

#include "BaseTypes.hpp"
#include "InstanceID.hpp"
#include "Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace snack
{
class BaseComponent;
class SceneManager;
class ScriptObject;
class Engine;

class ENGINE_API Transform final
{
    friend Engine;
    friend SceneManager;

public:

    Transform(Transform* pParent, InstanceID instanceId);

    ~Transform();

    template <typename T>
    T* AddComponent();

    BaseComponent* AddComponent(const std::string& id);

    void GetAllComponents(std::vector<BaseComponent*>& components);

    Transform* GetChild(int32 index) const;

    int32 GetChildCount() const; 

    template <typename T>
    T* GetComponent();
    
    BaseComponent* GetComponent(const std::string& id);

    int32 GetDepth() const;

    InstanceID GetInstanceID() const;

    glm::mat4 GetLocalMatrix() const;

    glm::mat4 GetWorldMatrix() const;

    std::string GetName() const;

    Transform* GetParent() const;

    glm::vec3 GetLocalPosition() const;

    glm::vec3 GetWorldPosition() const;

    glm::vec3 GetRotation() const;

    glm::vec3 GetScale() const;

    template <typename T>
    bool HasComponent();

    bool HasComponent(const std::string& id);

    bool IsEnabled() const;

    bool IsLeaf() const;

    bool IsScene() const;

    bool IsStatic() const;

    void Move(const glm::vec3& move);

    void Move(f32 x, f32 y, f32 z);

    void OnEditorInspector();

    template <typename T>
    bool RemoveComponent();

    bool RemoveComponent(const std::string& id);

    void Scale(const glm::vec3& scale);

    void Scale(f32 x, f32 y, f32 z);

    void SetEnabled(bool enabled);

    void SetName(const std::string& name);

    void SetParent(Transform* parent);

    void SetLocalPosition(const glm::vec3& position);

    void SetLocalPosition(f32 x, f32 y, f32 z);

    void SetRotation(const glm::vec3& position);

    void SetRotation(f32 x, f32 y, f32 z);

    void SetScale(const glm::vec3& position);

    void SetScale(f32 x, f32 y, f32 z);

    void SetScale(f32 uniform);

    void SetWorldPosition(const glm::vec3& position);

    void SetWorldPosition(f32 x, f32 y, f32 z);

private:

    InstanceID m_instanceID;
    std::string m_name;

    bool m_isEnabled;
    bool m_isStaic;
    bool m_isScene;

    int32 m_depth;

    std::unordered_map<std::string, BaseComponent*> m_components;
    std::unordered_map<std::string, ScriptObject*> m_scripts;

    std::vector<Transform*> m_children;
    Transform* m_parent;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

template<typename T>
T* Transform::AddComponent()
{
    auto itr = m_components.find(typeid(T).name());
    if (itr != m_components.end())
    {
        SPY_LOG_ERROR("Transform already has " << typeid(T).name() << " component attached to it.");
        return nullptr;
    }

    BaseComponent* component = new T(this);
    m_components.insert({ typeid(T).name(), component });
    return static_cast<T*>(component);
}

template<typename T>
T* Transform::GetComponent()
{
    BaseComponent* component = GetComponent(typeid(T).name());

    if (component)
    {
        return static_cast<T*>(component);
    }

    return nullptr;
}

template<typename T>
bool Transform::HasComponent()
{
    BaseComponent* component = GetComponent(typeid(T).name());

    if (component)
    {
        return true;
    }

    return false;
}

template<typename T>
bool Transform::RemoveComponent()
{
    return RemoveComponent(typeid(T).name());
}
} // namespace snack
