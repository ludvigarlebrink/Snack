#pragma once


#include "Managers/IScriptManager.hpp"

#include <glm/glm.hpp>

#define SOL_CHECK_ARGUMENTS 1
#include <iostream>
#include <sol/sol.hpp>

namespace snack
{
class ScriptManager final : public IScriptManager
{
public:

    ScriptManager();

    ~ScriptManager();

protected:

    void Tick(f32 deltaTime) override;

    void PostTick(f32 deltaTime) override;

private:

    void SetUp();

    void SetUpEngine();

    void SetUpMath();

    void TearDown();

private:

    sol::state lua;
};
} // namespace snack
