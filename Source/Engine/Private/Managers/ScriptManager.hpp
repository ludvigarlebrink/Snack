#pragma once

#include "Managers/IScriptManager.hpp"

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

    void TearDown();

private:


};
} // namespace snack
