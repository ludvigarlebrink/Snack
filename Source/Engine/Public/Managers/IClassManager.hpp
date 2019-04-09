#pragma once

#include "BaseTypes.hpp"

#include <string>
#include <vector>

namespace snack
{
class BaseComponent;
class Transform;

class ENGINE_API IClassManager
{
public:

    using ComponentConstructor = BaseComponent * (*)(Transform*);

    struct ComponentInfo
    {
        bool constructable;
        std::string name;
        std::string id;
        ComponentConstructor componentConstructor;
    };

public:

    virtual BaseComponent* CreateComponent(const std::string& id, Transform* transform) = 0;

    virtual void GetAllComponentInfo(std::vector<ComponentInfo>& componentInfos) = 0;

    virtual std::string GetComponentName(const std::string& id) = 0;

    template <typename T>
    void RegisterComponent(const std::string& name);

    template <typename T>
    void RegisterComponentUnconstructable(const std::string& name);

protected:

    virtual void RegisterComponent(const std::string& id, const std::string& name, ComponentConstructor componentConstructor) = 0;

    virtual void RegisterComponentUnconstructable(const std::string& id, const std::string& name) = 0;
};

template<typename T>
void IClassManager::RegisterComponent(const std::string& name)
{
    auto cb = [](Transform* transform)->BaseComponent*
    {
        return new T(transform);
    };
    RegisterComponent(typeid(T).name(), name, cb);
}

template<typename T>
void IClassManager::RegisterComponentUnconstructable(const std::string& name)
{
    RegisterComponentUnconstructable(typeid(T).name(), name);
}
} // namespace snack
