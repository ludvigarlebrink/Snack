#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace snack
{
class Engine;
class ScriptObject;

class IScriptManager
{
    friend Engine;

public:

    virtual ~IScriptManager() = default;

    virtual ScriptObject* CreateBehaviorObject(const std::string& className) = 0;

protected:

    virtual void Tick(f32 deltaTime) = 0;

    virtual void PostTick(f32 deltaTime) = 0;
};
} // namespace snack
