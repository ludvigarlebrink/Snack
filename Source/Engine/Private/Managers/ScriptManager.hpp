#pragma once

#include "Managers/IScriptManager.hpp"
#include "InstanceID.hpp"

#include <glm/glm.hpp>
#include <iostream>
#include <unordered_map>

#define SOL_CHECK_ARGUMENTS 1
#include <sol/sol.hpp>

namespace snack
{
class ScriptManager final : public IScriptManager
{
public:

    ScriptManager();

    ~ScriptManager();

    ScriptObject* CreateBehaviorObject(const std::string& className) override;

protected:

    void Tick(f32 deltaTime) override;

    void PostTick(f32 deltaTime) override;

private:

    void SetUp();

    void SetUpEngine();

    void SetUpMath();

    void TearDown();

private:

    sol::state* m_state;
    InstanceID m_nextInstanceID;

    std::unordered_map<std::string, std::vector<ScriptObject*>> m_behaviorObjects;
};
} // namespace snack
