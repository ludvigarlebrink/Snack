#include "SceneMoveTool.hpp"
#include "EditorManager.hpp"
#include "EngineInclude.hpp"
#include "SceneToolData.hpp"
#include "SketchInclude.hpp"
#include "UtilsInclude.hpp"

namespace spy
{
SceneMoveTool::SceneMoveTool()
    : m_mode(Mode::NONE)
    , m_offset(0.0f)
{
}

SceneMoveTool::~SceneMoveTool()
{
}

void SceneMoveTool::OnBegin()
{
    m_mode = Mode::NONE;
}

void SceneMoveTool::OnEnd()
{
}

void SceneMoveTool::OnTick(const SceneToolData& data)
{
    if (EditorManager::Scene()->GetSelectedTransformCount() == 1)
    {
        // Reset colors.
        m_xColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        m_yColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        m_zColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        m_xPanColor = glm::vec4(1.0f, 0.0f, 0.0f, 0.42f);
        m_yPanColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.42f);
        m_zPanColor = glm::vec4(0.0f, 0.0f, 1.0f, 0.42f);

        m_xPanColorQuad = glm::vec4(1.0f, 0.0f, 0.0f, 0.16f);
        m_yPanColorQuad = glm::vec4(0.0f, 1.0f, 0.0f, 0.16f);
        m_zPanColorQuad = glm::vec4(0.0f, 0.0f, 1.0f, 0.16f);

        Transform* transform = EditorManager::Scene()->GetSelectedTransform(0);
        glm::mat4 model = transform->GetWorldMatrix();

        // Fixed distance between the camera.
        glm::vec3 widgetPosition = glm::vec3(model[3]);
        f32 distance = glm::distance(widgetPosition, data.cameraPosition);
        glm::vec3 dir = glm::normalize(widgetPosition - data.cameraPosition);
        widgetPosition -= dir * (distance - 5.0f);

        glm::vec3 xAxis = glm::normalize(glm::vec3(model[0]));
        glm::vec3 yAxis = glm::normalize(glm::vec3(model[1]));
        glm::vec3 zAxis = glm::normalize(glm::vec3(model[2]));

        if (data.cameraMode || SketchEvent::ButtonUp(Button::LEFT))
        {
            m_mode = Mode::NONE;
        }

        glm::vec2 pointerCoords = SketchEvent::GetPointerPosition() - SketchWindow::GetPosition();
        pointerCoords.x = (2.0f * pointerCoords.x) / static_cast<f32>(data.width) - 1.0f;
        pointerCoords.y = 1.0f - (2.0f * pointerCoords.y) / static_cast<f32>(data.height);

        glm::vec4 rayClip = glm::vec4(pointerCoords.x, pointerCoords.y, -1.0f, 1.0f);
        glm::vec4 rayEye = glm::inverse(data.projectionMatrix) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
        glm::vec3 rayWorld = glm::vec3(data.viewInverse * rayEye);
        rayWorld = glm::normalize(rayWorld);

        if (!data.cameraMode && m_mode == Mode::NONE)
        {
            static const glm::vec3 xAabbMin = glm::vec3(0.0f, -0.025f, -0.025f);
            static const glm::vec3 xAabbMax = glm::vec3(1.0f, 0.025f, 0.025f);
            static const glm::vec3 xAabbMinHandle = glm::vec3(1.0f, -0.06f, -0.06f);
            static const glm::vec3 xAabbMaxHandle = glm::vec3(1.3f, 0.06f, 0.06f);
            static const glm::vec3 xAabbMinPan = glm::vec3(-0.025f, 0.0f, 0.0f);
            static const glm::vec3 xAabbMaxPan = glm::vec3(0.025f, 0.25f, 0.25f);

            static const glm::vec3 yAabbMin = glm::vec3(-0.025f, 0.0f, -0.025f);
            static const glm::vec3 yAabbMax = glm::vec3(0.025f, 1.0f, 0.025f);
            static const glm::vec3 yAabbMinHandle = glm::vec3(-0.06f, 1.0f, -0.06f);
            static const glm::vec3 yAabbMaxHandle = glm::vec3(0.06f, 1.3f, 0.06f);
            static const glm::vec3 yAabbMinPan = glm::vec3(0.0f, -0.025f, 0.0f);
            static const glm::vec3 yAabbMaxPan = glm::vec3(0.25f, 0.025f, 0.25f);

            static const glm::vec3 zAabbMin = glm::vec3(-0.025f, -0.025f, 0.0f);
            static const glm::vec3 zAabbMax = glm::vec3(0.025f, 0.025f, 1.0f);
            static const glm::vec3 zAabbMinHandle = glm::vec3(-0.06f, -0.06f, 1.0f);
            static const glm::vec3 zAabbMaxHandle = glm::vec3(0.06f, 0.06f, 1.3f);
            static const glm::vec3 zAabbMinPan = glm::vec3(0.0f, 0.0f, -0.025f);
            static const glm::vec3 zAabbMaxPan = glm::vec3(0.25f, 0.25f, 0.025f);

            glm::mat4 rayModel = model;
            rayModel[3].x = widgetPosition.x;
            rayModel[3].y = widgetPosition.y;
            rayModel[3].z = widgetPosition.z;

            f32 t = std::numeric_limits<f32>::max();
            bool hitPan = false;
            Axis axis = Axis::X_AXIS;

            Intersection::RayHitData rayHitData;
            if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, xAabbMinPan, xAabbMaxPan, rayModel, rayHitData))
            {
                hitPan = true;
                t = rayHitData.tMin;
                axis = Axis::X_AXIS;
            }

            if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, yAabbMinPan, yAabbMaxPan, rayModel, rayHitData))
            {
                if (rayHitData.tMin < t)
                {
                    hitPan = true;
                    t = rayHitData.tMin;
                    axis = Axis::Y_AXIS;
                }
            }

            if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, zAabbMinPan, zAabbMaxPan, rayModel, rayHitData))
            {
                if (rayHitData.tMin < t)
                {
                    hitPan = true;
                    t = rayHitData.tMin;
                    axis = Axis::Z_AXIS;
                }
            }

            if (hitPan)
            {
                if (axis == Axis::X_AXIS)
                {
                    m_xPanColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                    m_xPanColorQuad = glm::vec4(1.0f, 1.0f, 1.0f, 0.42f);
                    if (SketchEvent::ButtonDown(Button::LEFT))
                    {
                        m_mode = Mode::PAN_X_AXIS;
                        Intersection::RayHitData rayHitData;
                        if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, xAxis, glm::vec3(model[3]), rayHitData))
                        {
                            m_offsetPan = rayHitData.point - glm::vec3(model[3]);
                        }
                    }
                }
                else if (axis == Axis::Y_AXIS)
                {
                    m_yPanColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                    m_yPanColorQuad = glm::vec4(1.0f, 1.0f, 1.0f, 0.42f);
                    if (SketchEvent::ButtonDown(Button::LEFT))
                    {
                        m_mode = Mode::PAN_Y_AXIS;
                        Intersection::RayHitData rayHitData;
                        if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, yAxis, glm::vec3(model[3]), rayHitData))
                        {
                            m_offsetPan = rayHitData.point - glm::vec3(model[3]);
                        }
                    }
                }
                else if (axis == Axis::Z_AXIS)
                {
                    m_zPanColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                    m_zPanColorQuad = glm::vec4(1.0f, 1.0f, 1.0f, 0.42f);
                    if (SketchEvent::ButtonDown(Button::LEFT))
                    {
                        m_mode = Mode::PAN_Z_AXIS;
                        Intersection::RayHitData rayHitData;
                        if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, zAxis, glm::vec3(model[3]), rayHitData))
                        {
                            m_offsetPan = rayHitData.point - glm::vec3(model[3]);
                        }
                    }
                }
            }
            else if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, xAabbMin, xAabbMax, rayModel, rayHitData) ||
                Intersection::RayVsOBB(data.cameraPosition, rayWorld, xAabbMinHandle, xAabbMaxHandle, rayModel, rayHitData))
            {
                m_xColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                if (SketchEvent::ButtonDown(Button::LEFT))
                {
                    m_mode = Mode::MOVE_X_AXIS;
                    if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, yAxis, glm::vec3(model[3]), rayHitData))
                    {
                        m_offset = glm::distance(glm::vec3(model[3]) * xAxis, rayHitData.point * xAxis);
                    }
                }
            }
            else if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, yAabbMin, yAabbMax, rayModel, rayHitData) ||
                Intersection::RayVsOBB(data.cameraPosition, rayWorld, yAabbMinHandle, yAabbMaxHandle, rayModel, rayHitData))
            {
                m_yColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                if (SketchEvent::ButtonDown(Button::LEFT))
                {
                    m_mode = Mode::MOVE_Y_AXIS;
                    if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, xAxis, glm::vec3(model[3]), rayHitData))
                    {
                        m_offset = glm::distance(glm::vec3(model[3]) * yAxis, rayHitData.point * yAxis);
                    }
                }
            }
            else if (Intersection::RayVsOBB(data.cameraPosition, rayWorld, zAabbMin, zAabbMax, rayModel, rayHitData) ||
                Intersection::RayVsOBB(data.cameraPosition, rayWorld, zAabbMinHandle, zAabbMaxHandle, rayModel, rayHitData))
            {
                m_zColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                if (SketchEvent::ButtonDown(Button::LEFT))
                {
                    m_mode = Mode::MOVE_Z_AXIS;
                    if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, yAxis, glm::vec3(model[3]), rayHitData))
                    {
                        m_offset = glm::distance(glm::vec3(model[3]) * zAxis, rayHitData.point * zAxis);
                    }
                }
            }
        }
        else if (m_mode == Mode::MOVE_X_AXIS)
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
                        transform->Move(xAxis * (dist - m_offset));
                    }
                    else if (dotProduct < 0.0f)
                    {
                        transform->Move(-xAxis * (dist + m_offset));
                    }
                }
            }
        }
        else if (m_mode == Mode::MOVE_Y_AXIS)
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
                        transform->Move(yAxis * (dist - m_offset));
                    }
                    else if (dotProduct < 0.0f)
                    {
                        transform->Move(-yAxis * (dist + m_offset));
                    }
                }
            }
        }
        else if (m_mode == Mode::MOVE_Z_AXIS)
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
                        transform->Move(zAxis * (dist - m_offset));
                    }
                    else if (dotProduct < 0.0f)
                    {
                        transform->Move(-zAxis * (dist + m_offset));
                    }
                }
            }
        }
        else if (m_mode == Mode::PAN_X_AXIS)
        {
            m_xPanColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            m_xPanColorQuad = glm::vec4(1.0f, 1.0f, 1.0f, 0.42f);
            Intersection::RayHitData rayHitData;
            if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, xAxis, glm::vec3(model[3]), rayHitData))
            {
                glm::vec3 moveDir = rayHitData.point - glm::vec3(model[3]);
                transform->Move(moveDir - m_offsetPan);
            }
        }
        else if (m_mode == Mode::PAN_Y_AXIS)
        {
            m_yPanColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            m_yPanColorQuad = glm::vec4(1.0f, 1.0f, 1.0f, 0.42f);
            Intersection::RayHitData rayHitData;
            if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, yAxis, glm::vec3(model[3]), rayHitData))
            {
                glm::vec3 moveDir = rayHitData.point - glm::vec3(model[3]);
                transform->Move(moveDir - m_offsetPan);
            }
        }
        else if (m_mode == Mode::PAN_Z_AXIS)
        {
            m_zPanColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            m_zPanColorQuad = glm::vec4(1.0f, 1.0f, 1.0f, 0.42f);
            Intersection::RayHitData rayHitData;
            if (Intersection::RayVsPlane(data.cameraPosition, rayWorld, zAxis, glm::vec3(model[3]), rayHitData))
            {
                glm::vec3 moveDir = rayHitData.point - glm::vec3(model[3]);
                transform->Move(moveDir - m_offsetPan);
            }
        }

        Draw(xAxis, yAxis, zAxis, widgetPosition);
    }
}

void SceneMoveTool::Draw(const glm::vec3& xAxis, const glm::vec3& yAxis, const glm::vec3& zAxis, const glm::vec3& position)
{
    glm::vec3 p0 = position;

    {
        glm::vec3 p1 = yAxis * 0.25f + position;
        glm::vec3 p2 = zAxis * 0.25f + position;
        glm::vec3 p3 = yAxis * 0.25f + zAxis * 0.25f + position;

        SketchGizmo::LineOverdrawn(p1, p3, m_xPanColor);
        SketchGizmo::LineOverdrawn(p2, p3, m_xPanColor);
        SketchGizmo::QuadOverdrawn(p0, p2, p3, p1, m_xPanColorQuad);
    }

    {
        glm::vec3 p1 = zAxis * 0.25f + position;
        glm::vec3 p2 = xAxis * 0.25f + position;
        glm::vec3 p3 = zAxis * 0.25f + xAxis * 0.25f + position;

        SketchGizmo::LineOverdrawn(p1, p3, m_yPanColor);
        SketchGizmo::LineOverdrawn(p2, p3, m_yPanColor);
        SketchGizmo::QuadOverdrawn(p0, p2, p3, p1, m_yPanColorQuad);
    }

    {
        glm::vec3 p1 = xAxis * 0.25f + position;
        glm::vec3 p2 = yAxis * 0.25f + position;
        glm::vec3 p3 = xAxis * 0.25f + yAxis * 0.25f + position;

        SketchGizmo::LineOverdrawn(p1, p3, m_zPanColor);
        SketchGizmo::LineOverdrawn(p2, p3, m_zPanColor);
        SketchGizmo::QuadOverdrawn(p0, p2, p3, p1, m_zPanColorQuad);
    }

    SketchGizmo::LineOverdrawn(position, xAxis + position, m_xColor);
    SketchGizmo::LineOverdrawn(position, yAxis + position, m_yColor);
    SketchGizmo::LineOverdrawn(position, zAxis + position, m_zColor);

    SketchGizmo::ConeOverdrawn(xAxis + position, xAxis, yAxis, 0.12f, 0.25f, m_xColor);
    SketchGizmo::ConeOverdrawn(yAxis + position, yAxis, zAxis, 0.12f, 0.25f, m_yColor);
    SketchGizmo::ConeOverdrawn(zAxis + position, zAxis, xAxis, 0.12f, 0.25f, m_zColor);
}
} // namespace spy
