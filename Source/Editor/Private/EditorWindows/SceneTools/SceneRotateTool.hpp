#pragma once

#include "ISceneTool.hpp"

#include <glm/glm.hpp>

namespace spy
{
class SceneRotateTool final : public ISceneTool
{
private:

    enum class Mode
    {
        NONE,
        ROTATE_X,
        ROTATE_Y,
        ROTATE_Z
    };

public:

    SceneRotateTool();

    ~SceneRotateTool();

    void OnBegin() override;

    void OnEnd() override;

    void OnTick(const SceneToolData& data) override;

private:

    Mode m_mode;
};
} // namespace spy
