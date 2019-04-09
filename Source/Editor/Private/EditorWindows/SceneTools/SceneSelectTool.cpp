#include "SceneSelectTool.hpp"
#include "EditorManager.hpp"
#include "EngineInclude.hpp"
#include "SceneToolData.hpp"
#include "SketchInclude.hpp"
#include "UtilsInclude.hpp"

namespace snack
{
SceneSelectTool::SceneSelectTool()
{
}

SceneSelectTool::~SceneSelectTool()
{
}

void SceneSelectTool::OnBegin()
{
}

void SceneSelectTool::OnEnd()
{
}

void SceneSelectTool::OnTick(const SceneToolData& data)
{
    if (!data.cameraMode && SketchEvent::IsPointerOverWindow() && SketchEvent::ButtonDown(Button::LEFT))
    {
        glm::vec2 pointerCoords = SketchEvent::GetPointerPosition() - SketchWindow::GetPosition();
        pointerCoords.x = (2.0f * pointerCoords.x) / static_cast<f32>(data.width) - 1.0f;
        pointerCoords.y = 1.0f - (2.0f * pointerCoords.y) / static_cast<f32>(data.height);

        glm::vec4 rayClip = glm::vec4(pointerCoords.x, pointerCoords.y, -1.0f, 1.0f);
        glm::vec4 rayEye = glm::inverse(data.projection) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
        glm::vec3 rayWorld = glm::vec3(data.viewInverse * rayEye);
        rayWorld = glm::normalize(rayWorld);

        Transform* transform = Manager::Render()->PickMesh(data.cameraPosition, rayWorld);
        if (SketchEvent::ModRepeat(Mod::SHIFT) && transform)
        {
            bool erased = false;
            for (int32 i = 0; i < EditorManager::Scene()->GetSelectedTransformCount(); ++i)
            {
                if (EditorManager::Scene()->GetSelectedTransform(i) == transform)
                {
                    EditorManager::Scene()->RemoveSelectedTransfrom(i);
                    erased = true;
                    break;
                }
            }

            if (!erased)
            {
                EditorManager::Scene()->PushSelectedTransfrom(transform);
            }
        }
        else
        {
            EditorManager::Scene()->ClearSelectedTransforms();
            if (transform)
            {
                EditorManager::Scene()->PushSelectedTransfrom(transform);
            }
        }
    }
}
} // namespace snack
