#pragma once

#include "BaseTypes.hpp"

namespace snack
{
struct SceneToolData;

class ISceneTool
{
public:

    virtual ~ISceneTool() = default;

    virtual void OnBegin() = 0;

    virtual void OnEnd() = 0;

    virtual void OnTick(const SceneToolData& data) = 0;
};
} // namespace snack
