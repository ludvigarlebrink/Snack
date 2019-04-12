#include "SceneScaleTool.hpp"
#include "EditorManager.hpp"
#include "EngineInclude.hpp"
#include "SceneToolData.hpp"
#include "SketchInclude.hpp"
#include "UtilsInclude.hpp"

namespace snack
{
SceneScaleTool::SceneScaleTool()
    : m_mode(Mode::NONE)
{
}

SceneScaleTool::~SceneScaleTool()
{
}

void SceneScaleTool::OnBegin()
{
    m_mode = Mode::NONE;
}

void SceneScaleTool::OnEnd()
{
}

void SceneScaleTool::OnTick(const SceneToolData& data)
{
    if (EditorManager::Scene()->GetSelectedTransformCount() == 1)
    {
        // Reset colors.
        m_uniformColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        m_xColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        m_yColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        m_zColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        Transform* transform = EditorManager::Scene()->GetSelectedTransform(0);
        glm::mat4 model = transform->GetWorldMatrix();

        // Fixed distance between the camera.
        glm::vec3 widgetPosition = glm::vec3(model[3]);
        f32 distance = glm::distance(widgetPosition, data.cameraPosition);
        glm::vec3 dir = glm::normalize(widgetPosition - data.cameraPosition);
        widgetPosition -= dir * (distance - 5.0f);

        glm::vec3 xAxis = glm::normalize(model[0]);
        glm::vec3 yAxis = glm::normalize(model[1]);
        glm::vec3 zAxis = glm::normalize(model[2]);

        glm::mat4 centerModel = model;
        centerModel[0] = glm::vec4(xAxis * 0.125f, 0.0f);
        centerModel[1] = glm::vec4(yAxis * 0.125f, 0.0f);
        centerModel[2] = glm::vec4(zAxis * 0.125f, 0.0f);
        centerModel[3] = glm::vec4(widgetPosition, 1.0f);

        if (data.cameraMode || SketchEvent::ButtonUp(Button::LEFT))
        {
            m_mode = Mode::NONE;
        }

        glm::vec2 pointerCoords = SketchEvent::GetPointerPosition() - SketchWindow::GetPosition();
        pointerCoords.x = (2.0f * pointerCoords.x) / static_cast<f32>(data.width) - 1.0f;
        pointerCoords.y = 1.0f - (2.0f * pointerCoords.y) / static_cast<f32>(data.height);

        glm::vec4 rayClip = glm::vec4(pointerCoords.x, pointerCoords.y, -1.0f, 1.0f);
        glm::vec4 rayEye = glm::inverse(data.projection) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
        glm::vec3 rayWorld = glm::vec3(data.viewInverse * rayEye);
        rayWorld = glm::normalize(rayWorld);

        if (!data.cameraMode && m_mode == Mode::NONE)
        {
            static const glm::vec3 uniformAabbMinHandle = glm::vec3(-0.0625f, -0.0625f, -0.0625f);
            static const glm::vec3 uniformAabbMaxHandle = glm::vec3(0.0625f, 0.0625f, 0.0625f);

            static const glm::vec3 xAabbMin = glm::vec3(0.0f, -0.025f, -0.025f);
            static const glm::vec3 xAabbMax = glm::vec3(1.0f, 0.025f, 0.025f);
            static const glm::vec3 xAabbMinHandle = glm::vec3(1.0f, -0.0625f, -0.0625f);
            static const glm::vec3 xAabbMaxHandle = glm::vec3(1.125f, 0.0625f, 0.0625f);

            static const glm::vec3 yAabbMin = glm::vec3(-0.025f, 0.0f, -0.025f);
            static const glm::vec3 yAabbMax = glm::vec3(0.025f, 1.0f, 0.025f);
            static const glm::vec3 yAabbMinHandle = glm::vec3(-0.0625f, 1.0f, -0.0625f);
            static const glm::vec3 yAabbMaxHandle = glm::vec3(0.0625f, 1.125f, 0.0625f);

            static const glm::vec3 zAabbMin = glm::vec3(-0.025f, -0.025f, 0.0f);
            static const glm::vec3 zAabbMax = glm::vec3(0.025f, 0.025f, 1.0f);
            static const glm::vec3 zAabbMinHandle = glm::vec3(-0.0625f, -0.0625f, 1.0f);
            static const glm::vec3 zAabbMaxHandle = glm::vec3(0.0625f, 0.0625f, 1.125f);

            glm::mat4 rayModel = model;
            rayModel[0] = glm::vec4(xAxis, rayModel[3].x);
            rayModel[1] = glm::vec4(yAxis, rayModel[3].y);
            rayModel[2] = glm::vec4(zAxis, rayModel[3].z);
            rayModel[3] = glm::vec4(widgetPosition, 1.0f);

            Intersection::RayHitData rayHitData;
            if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, uniformAabbMinHandle, uniformAabbMaxHandle, rayModel, rayHitData))
            {
                m_uniformColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                if (SketchEvent::ButtonDown(Button::LEFT))
                {
                    m_mode = Mode::SCALE_UNIFORM;
                }
            }
            else if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, xAabbMin, xAabbMax, rayModel, rayHitData) ||
                Intersection::RayVsOBB(data.cameraPosition, rayWorld, xAabbMinHandle, xAabbMaxHandle, rayModel, rayHitData))
            {
                m_xColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                if (SketchEvent::ButtonDown(Button::LEFT))
                {
                    m_mode = Mode::SCALE_X_AXIS;
                    if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, yAxis, glm::vec3(model[3]), rayHitData))
                    {
                        m_offset = glm::distance(glm::vec3(model[3]) * xAxis, rayHitData.point * xAxis);
                        m_offsetScale = transform->GetScale();
                    }
                }
            }
            else if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, yAabbMin, yAabbMax, rayModel, rayHitData) ||
                Intersection::RayVsOBB(data.cameraPosition, rayWorld, yAabbMinHandle, yAabbMaxHandle, rayModel, rayHitData))
            {
                m_yColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                if (SketchEvent::ButtonDown(Button::LEFT))
                {
                    m_mode = Mode::SCALE_Y_AXIS;
                    if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, xAxis, glm::vec3(model[3]), rayHitData))
                    {
                        m_offset = glm::distance(glm::vec3(model[3]) * yAxis, rayHitData.point * yAxis);
                        m_offsetScale = transform->GetScale();
                    }
                }
            }
            else if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, zAabbMin, zAabbMax, rayModel, rayHitData) ||
                Intersection::RayVsOBB(data.cameraPosition, rayWorld, zAabbMinHandle, zAabbMaxHandle, rayModel, rayHitData))
            {
                m_zColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                if (SketchEvent::ButtonDown(Button::LEFT))
                {
                    m_mode = Mode::SCALE_Z_AXIS;
                    if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, yAxis, glm::vec3(model[3]), rayHitData))
                    {
                        m_offset = glm::distance(glm::vec3(model[3]) * zAxis, rayHitData.point * zAxis);
                        m_offsetScale = transform->GetScale();
                    }
                }
            }
        }
        else if (m_mode == Mode::SCALE_UNIFORM)
        {
            m_uniformColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
        else if (m_mode == Mode::SCALE_X_AXIS)
        {
            m_xColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            Intersection::RayHitData rayHitData;
            if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, yAxis, glm::vec3(model[3]), rayHitData))
            {
                f32 dist = glm::distance(glm::vec3(model[3]) * xAxis, rayHitData.point * xAxis);
                if (dist > 0.0001f)
                {
                    f32 dotProduct = glm::dot(xAxis, glm::normalize(rayHitData.point - glm::vec3(model[3])));
                    if (dotProduct > 0.0f)
                    {
                        transform->SetScale(m_offsetScale.x + dist - m_offset, m_offsetScale.y, m_offsetScale.z);
                    }
                    else if (dotProduct < 0.0f)
                    {
                        transform->SetScale(m_offsetScale.x - dist - m_offset, m_offsetScale.y, m_offsetScale.z);
                    }
                }
            }
        }
        else if (m_mode == Mode::SCALE_Y_AXIS)
        {
            m_yColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            Intersection::RayHitData rayHitData;
            if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, xAxis, glm::vec3(model[3]), rayHitData))
            {
                f32 dist = glm::distance(glm::vec3(model[3]) * yAxis, rayHitData.point * yAxis);
                if (dist > 0.0001f)
                {
                    f32 dotProduct = glm::dot(yAxis, glm::normalize(rayHitData.point - glm::vec3(model[3])));
                    if (dotProduct > 0.0f)
                    {
                        transform->SetScale(m_offsetScale.x, m_offsetScale.y + dist - m_offset, m_offsetScale.z);
                    }
                    else if (dotProduct < 0.0f)
                    {
                        transform->SetScale(m_offsetScale.x, m_offsetScale.y - dist - m_offset, m_offsetScale.z);
                    }
                }
            }
        }
        else if (m_mode == Mode::SCALE_Z_AXIS)
        {
            m_zColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            Intersection::RayHitData rayHitData;
            if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, yAxis, glm::vec3(model[3]), rayHitData))
            {
                f32 dist = glm::distance(glm::vec3(model[3]) * zAxis, rayHitData.point * zAxis);
                if (dist > 0.0001f)
                {
                    f32 dotProduct = glm::dot(zAxis, glm::normalize(rayHitData.point - glm::vec3(model[3])));
                    if (dotProduct > 0.0f)
                    {
                        transform->SetScale(m_offsetScale.x, m_offsetScale.y, m_offsetScale.z + dist - m_offset);
                    }
                    else if (dotProduct < 0.0f)
                    {
                        transform->SetScale(m_offsetScale.x, m_offsetScale.y, m_offsetScale.z - dist - m_offset);
                    }
                }
            }
        }

        SketchGizmo::CubeOverdrawn(centerModel, m_uniformColor);

        {
            glm::mat4 xModel = centerModel;
            xModel[3] += glm::vec4(xAxis * 1.0625f, 0.0f);
            SketchGizmo::CubeOverdrawn(xModel, m_xColor);
        }

        {
            glm::mat4 yModel = centerModel;
            yModel[3] += glm::vec4(yAxis * 1.0625f, 0.0f);
            SketchGizmo::CubeOverdrawn(yModel, m_yColor);
        }

        {
            glm::mat4 zModel = centerModel;
            zModel[3] += glm::vec4(zAxis * 1.0625f, 0.0f);
            SketchGizmo::CubeOverdrawn(zModel, m_zColor);
        }

        // Has to be normalized due to scaling.
        SketchGizmo::LineOverdrawn(widgetPosition, xAxis + widgetPosition, m_xColor);
        SketchGizmo::LineOverdrawn(widgetPosition, yAxis + widgetPosition, m_yColor);
        SketchGizmo::LineOverdrawn(widgetPosition, zAxis + widgetPosition, m_zColor);
    }
}
} // namespace snack
