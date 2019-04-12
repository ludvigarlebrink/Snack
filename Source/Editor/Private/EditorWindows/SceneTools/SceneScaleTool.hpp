#pragma once

#include "ISceneTool.hpp"

#include <glm/glm.hpp>

namespace snack
{
class SceneScaleTool final : public ISceneTool
{
public:

    enum class Mode
    {
        NONE,
        SCALE_UNIFORM,
        SCALE_X_AXIS,
        SCALE_Y_AXIS,
        SCALE_Z_AXIS
    };

public:

    SceneScaleTool();

    ~SceneScaleTool();

    void OnBegin() override;

    void OnEnd() override;

    void OnTick(const SceneToolData& data) override;

private:

    Mode m_mode;

    f32 m_offset;
    glm::vec3 m_offsetScale;

    glm::vec4 m_uniformColor;
    glm::vec4 m_xColor;
    glm::vec4 m_yColor;
    glm::vec4 m_zColor;
};
} // namespace snack
