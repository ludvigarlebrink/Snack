#include "ClassManager.hpp"
#include "Components/BaseComponent.hpp"

namespace spy
{
BaseComponent* ClassManager::CreateComponent(const std::string& id, Transform* transform)
{
    return m_componentInfos[id].componentConstructor(transform);
}

void ClassManager::GetAllComponentInfo(std::vector<ClassManager::ComponentInfo>& componentInfos)
{
    for (auto& info : m_componentInfos)
    {
        componentInfos.push_back(info.second);
    }
}

std::string ClassManager::GetComponentName(const std::string& id)
{
    auto itr = m_componentInfos.find(id);
    if (itr != m_componentInfos.end())
    {
        return itr->second.name;
    }
    
    return "";
}

void ClassManager::RegisterComponent(const std::string& id, const std::string& name, ComponentConstructor componentConstructor)
{
    ComponentInfo componentInfo;
    componentInfo.constructable = true;
    componentInfo.id = id;
    componentInfo.name = name;
    componentInfo.componentConstructor = componentConstructor;
    m_componentInfos.insert({ id, componentInfo });
}

void ClassManager::RegisterComponentUnconstructable(const std::string& id, const std::string& name)
{
    ComponentInfo componentInfo;
    componentInfo.constructable = false;
    componentInfo.id = id;
    componentInfo.name = name;
    componentInfo.componentConstructor = nullptr;
    m_componentInfos.insert({ id, componentInfo });
}
} // namespace spy
