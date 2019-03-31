#pragma once

#include "BaseTypes.hpp"
#include "EditorWindow.hpp"
#include "RenderCoreForward.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace spy
{
class ISceneTool;
class SceneMoveTool;
class SceneRotateTool;
class SceneScaleTool;
class SceneSelectTool;

class EDITOR_API SceneWindow final : public EditorWindow
{
private:

    enum class Mode
    {
        SELECT,
        MOVE,
        ROTATE,
        SCALE
    };

public:

    SceneWindow();

    ~SceneWindow();

    std::string GetTitle() override;

protected:

    void OnDraw(f32 deltaTime) override;

private:

    void DrawGizmos();

    void DrawGrid();

    void DrawScene(f32 deltaTime);

    void RotateMode();

    void ScaleMode();

    void SelectMode();

    void SetUp();

    void TearDown();

private:

    bool m_isGridEnabled;
    bool m_cameraMode;
    f32 m_fieldOfView;
    f32 m_moveSpeed;
    f32 m_rotateSpeed;
    int32 m_height;
    int32 m_width;
    uint32 m_selectedShadingMode;
    Mode m_mode;

    ISceneTool* m_activeSceneTool;
    SceneMoveTool* m_moveTool;
    SceneRotateTool* m_rotateTool;
    SceneScaleTool* m_scaleTool;
    SceneSelectTool* m_selectTool;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec2 m_pointerGlobalPosition;

    Texture* m_texture;
    Renderbuffer* m_depthStencil;
    Framebuffer* m_framebuffer;
};
} // namespace spy
