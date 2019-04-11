#pragma once

#include "ISceneTool.hpp"

#include <glm/glm.hpp>

namespace snack
{
class SceneMoveTool final : public ISceneTool
{
private:

    enum class Mode
    {
        NONE,
        MOVE_X_AXIS,
        MOVE_Y_AXIS,
        MOVE_Z_AXIS,
        PAN_X_AXIS,
        PAN_Y_AXIS,
        PAN_Z_AXIS
    };

public:

    SceneMoveTool();

    ~SceneMoveTool();

    void OnBegin() override;

    void OnEnd() override;

    void OnTick(const SceneToolData& data) override;

private:

    void Draw(const glm::vec3& xAxis, const glm::vec3& yAxis, const glm::vec3& zAxis, const glm::vec3& position);

private:

    Mode m_mode;

    f32 m_offset;
    glm::vec3 m_offsetPan;

    glm::vec4 m_xColor;
    glm::vec4 m_yColor;
    glm::vec4 m_zColor;

    glm::vec4 m_xPanColor;
    glm::vec4 m_yPanColor;
    glm::vec4 m_zPanColor;

    glm::vec4 m_xPanColorQuad;
    glm::vec4 m_yPanColorQuad;
    glm::vec4 m_zPanColorQuad;
};
} // namespace snack
