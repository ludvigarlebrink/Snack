#pragma once

#include "ISceneTool.hpp"

#include <glm/glm.hpp>

namespace snack
{
class SceneScaleTool final : public ISceneTool
{
public:

    SceneScaleTool();

    ~SceneScaleTool();

    void OnBegin() override;

    void OnEnd() override;

    void OnTick(const SceneToolData& data) override;
};
} // namespace snack
