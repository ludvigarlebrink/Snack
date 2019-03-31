#pragma once

#include "ISceneTool.hpp"

namespace spy
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
} // namespace spy
