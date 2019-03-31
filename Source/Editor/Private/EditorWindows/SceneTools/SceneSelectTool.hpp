#pragma once

#include "ISceneTool.hpp"

namespace spy
{
class SceneSelectTool final : public ISceneTool
{
public:

    SceneSelectTool();

    ~SceneSelectTool();

    void OnBegin() override;

    void OnEnd() override;

    void OnTick(const SceneToolData& data) override;
};
} // namespace spy
