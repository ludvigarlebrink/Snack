#include "SceneRotateTool.hpp"
#include "EditorManager.hpp"
#include "EngineInclude.hpp"
#include "SceneToolData.hpp"
#include "SketchInclude.hpp"
#include "UtilsInclude.hpp"

namespace snack
{
SceneRotateTool::SceneRotateTool()
    : m_mode(Mode::NONE)
{
}

SceneRotateTool::~SceneRotateTool()
{
}

void SceneRotateTool::OnBegin()
{
    m_mode = Mode::NONE;
}

void SceneRotateTool::OnEnd()
{
}

void SceneRotateTool::OnTick(const SceneToolData& data)
{
    if (EditorManager::Scene()->GetSelectedTransformCount() == 1)
    {
        Transform* transform = EditorManager::Scene()->GetSelectedTransform(0);
        glm::mat4 model = transform->GetWorldMatrix();
        model[0] = glm::vec4(glm::normalize(glm::vec3(model[0])), model[0][3]);
        model[1] = glm::vec4(glm::normalize(glm::vec3(model[1])), model[1][3]);
        model[2] = glm::vec4(glm::normalize(glm::vec3(model[2])), model[2][3]);

        // Correct distance.
        glm::vec3 center = model[3];
        f32 distance = glm::distance(center, data.cameraPosition);
        glm::vec3 dir = glm::normalize(center - data.cameraPosition);
        center -= dir * (distance - 5.0f);

        glm::vec4 xColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 yColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        glm::vec4 zColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        glm::vec2 pointerCoords = SketchEvent::GetPointerPosition() - SketchWindow::GetPosition();
        pointerCoords.x = (2.0f * pointerCoords.x) / static_cast<f32>(data.width) - 1.0f;
        pointerCoords.y = 1.0f - (2.0f * pointerCoords.y) / static_cast<f32>(data.height);

        glm::vec4 rayClip = glm::vec4(pointerCoords.x, pointerCoords.y, -1.0f, 1.0f);
        glm::vec4 rayEye = glm::inverse(data.projection) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
        glm::vec3 rayWorld = glm::vec3(data.viewInverse * rayEye);
        rayWorld = glm::normalize(rayWorld);

        Intersection::RayHitData rayHitData;
        if (Intersection::RayVsSphere(data.cameraPosition, rayWorld, center, 1.0f, rayHitData))
        {
            glm::vec3 maxNormal = glm::normalize((data.cameraPosition + rayHitData.tMax * rayWorld) - center);

            // Test x.
            glm::vec3 xTestVectorMin = glm::normalize(glm::cross(rayHitData.normal, glm::vec3(model[2])));
            glm::vec3 xTestVectorMax = glm::normalize(glm::cross(maxNormal, glm::vec3(model[2])));
            glm::vec3 yTestVectorMin = glm::normalize(glm::cross(rayHitData.normal, glm::vec3(model[0])));
            glm::vec3 yTestVectorMax = glm::normalize(glm::cross(maxNormal, glm::vec3(model[0])));
            glm::vec3 zTestVectorMin = glm::normalize(glm::cross(rayHitData.normal, glm::vec3(model[1])));
            glm::vec3 zTestVectorMax = glm::normalize(glm::cross(maxNormal, glm::vec3(model[1])));

            if (glm::abs(glm::dot(xTestVectorMin, glm::vec3(model[0]))) > 0.98f ||
                glm::abs(glm::dot(xTestVectorMax, glm::vec3(model[0]))) > 0.98f)
            {
                xColor = glm::vec4(1.0f, 0.82f, 0.82f, 1.0f);
            }
            else if (glm::abs(glm::dot(yTestVectorMin, glm::vec3(model[1]))) > 0.98f ||
                glm::abs(glm::dot(yTestVectorMax, glm::vec3(model[1]))) > 0.98f)
            {
                yColor = glm::vec4(0.82f, 1.0f, 0.82f, 1.0f);
            }
            else if (glm::abs(glm::dot(zTestVectorMin, glm::vec3(model[2]))) > 0.98f ||
                glm::abs(glm::dot(zTestVectorMax, glm::vec3(model[2]))) > 0.98f)
            {
                zColor = glm::vec4(0.82f, 0.82f, 1.0f, 1.0f);
            }
        }

        for (int32 i = 0; i < 360; i += 18)
        {
            glm::mat3 rot0 = glm::mat3(model * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<f32>(i)), glm::vec3(0.0f, 0.0f, 1.0f)));
            glm::mat3 rot1 = glm::mat3(model * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<f32>(i) + 18.0f), glm::vec3(0.0f, 0.0f, 1.0f)));

            glm::mat3 rot2 = glm::mat3(model * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<f32>(i)), glm::vec3(0.0f, 1.0f, 0.0f)));
            glm::mat3 rot3 = glm::mat3(model * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<f32>(i) + 18.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

            glm::mat3 rot4 = glm::mat3(model * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<f32>(i)), glm::vec3(1.0f, 0.0f, 0.0f)));
            glm::mat3 rot5 = glm::mat3(model * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<f32>(i) + 18.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

            // Has to be normalized due to scaling.
            SketchGizmo::LineOverdrawn(rot4[2] + center, rot5[2] + center, xColor);
            SketchGizmo::LineOverdrawn(rot2[0] + center, rot3[0] + center, yColor);
            SketchGizmo::LineOverdrawn(rot0[1] + center, rot1[1] + center, zColor);
        }
    }
}
} // namespace snack
