#pragma once

#include "BaseTypes.hpp"

namespace snack
{
class Engine;

class IScriptManager
{
    friend Engine;

public:

    virtual ~IScriptManager() = default;

protected:

    virtual void Tick(f32 deltaTime) = 0;

    virtual void PostTick(f32 deltaTime) = 0;
};
} // namespace snack
