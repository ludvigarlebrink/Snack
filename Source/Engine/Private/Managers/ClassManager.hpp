#pragma once

#include "Managers/IClassManager.hpp"

#include <unordered_map>

namespace snack
{
class ClassManager final : public IClassManager
{
public:

    BaseComponent* CreateComponent(const std::string& id, Transform* transform) override;

    void GetAllComponentInfo(std::vector<ComponentInfo>& componentInfos) override;

    std::string GetComponentName(const std::string& id) override;

protected:

    void RegisterComponent(const std::string& id, const std::string& name, ComponentConstructor componentConstructor) override;

    void RegisterComponentUnconstructable(const std::string& id, const std::string& name) override;

private:

    std::unordered_map<std::string, ComponentInfo> m_componentInfos;
};
} // namespace snack
