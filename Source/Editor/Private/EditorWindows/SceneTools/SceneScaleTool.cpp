#include "SceneScaleTool.hpp"
#include "EditorManager.hpp"
#include "EngineInclude.hpp"
#include "SceneToolData.hpp"
#include "SketchInclude.hpp"
#include "UtilsInclude.hpp"

namespace spy
{
SceneScaleTool::SceneScaleTool()
{
}

SceneScaleTool::~SceneScaleTool()
{
}

void SceneScaleTool::OnBegin()
{
}

void SceneScaleTool::OnEnd()
{
}

void SceneScaleTool::OnTick(const SceneToolData& data)
{
    if (EditorManager::Scene()->GetSelectedTransformCount() == 1)
    {
        Transform* transform = EditorManager::Scene()->GetSelectedTransform(0);
        glm::mat4 model = transform->GetWorldMatrix();
        glm::vec3 widgetPosition = model[3];

        glm::vec3 xAxis = glm::normalize(model[0]);
        glm::vec3 yAxis = glm::normalize(model[1]);
        glm::vec3 zAxis = glm::normalize(model[2]);

        glm::mat4 centerModel = model;
        centerModel[0] = glm::vec4(xAxis * 0.125f, 0.0f);
        centerModel[1] = glm::vec4(yAxis * 0.125f, 0.0f);
        centerModel[2] = glm::vec4(zAxis * 0.125f, 0.0f);
        centerModel[3] = model[3];

        SketchGizmo::CubeOverdrawn(centerModel, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

        {
            glm::mat4 xModel = centerModel;
            xModel[3] += glm::vec4(xAxis * 1.0625f, 0.0f);
            SketchGizmo::CubeOverdrawn(xModel, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        }

        {
            glm::mat4 yModel = centerModel;
            yModel[3] += glm::vec4(yAxis * 1.0625f, 0.0f);
            SketchGizmo::CubeOverdrawn(yModel, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        }

        {
            glm::mat4 zModel = centerModel;
            zModel[3] += glm::vec4(zAxis * 1.0625f, 0.0f);
            SketchGizmo::CubeOverdrawn(zModel, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        }

        // Has to be normalized due to scaling.
        SketchGizmo::LineOverdrawn(widgetPosition, xAxis + widgetPosition, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        SketchGizmo::LineOverdrawn(widgetPosition, yAxis + widgetPosition, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        SketchGizmo::LineOverdrawn(widgetPosition, zAxis + widgetPosition, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

    }
}
} // namespace spy
