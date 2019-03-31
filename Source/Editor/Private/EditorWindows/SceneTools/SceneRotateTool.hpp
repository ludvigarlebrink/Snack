#pragma once

#include "ISceneTool.hpp"

namespace spy
{
class SceneRotateTool final : public ISceneTool
{
public:

    SceneRotateTool();

    ~SceneRotateTool();

    void OnBegin() override;

    void OnEnd() override;

    void OnTick(const SceneToolData& data) override;
};
} // namespace spy
