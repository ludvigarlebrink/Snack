#pragma once

#include "EditorWindow.hpp"
#include "EngineForward.hpp"
#include "Managers/IClassManager.hpp"

namespace snack
{
class EDITOR_API InspectorWindow final : public EditorWindow
{
public:

    InspectorWindow();

    ~InspectorWindow();

    std::string GetTitle() override;

protected:

    void OnDraw(f32 deltaTime) override;

private:

    std::string m_search;
    std::vector<IClassManager::ComponentInfo> m_componentInfos;
};
} // namespace snack
