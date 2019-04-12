#include "ScriptManager.hpp"

namespace snack
{
ScriptManager::ScriptManager()
{
    SetUp();
}

ScriptManager::~ScriptManager()
{
    TearDown();
}

void ScriptManager::Tick(f32 deltaTime)
{
}

void ScriptManager::PostTick(f32 deltaTime)
{
}

void ScriptManager::SetUp()
{
}

void ScriptManager::TearDown()
{
}
} // namespace snack
