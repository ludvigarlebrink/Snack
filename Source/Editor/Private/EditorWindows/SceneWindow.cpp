#include "EditorWindows/SceneWindow.hpp"
#include "EditorManager.hpp"
#include "EngineInclude.hpp"
#include "UtilsInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"
#include "SketchInternal.hpp"

#include <string>

namespace spy
{
SceneWindow::SceneWindow()
    : m_isGridEnabled(true)
    , m_cameraMode(false)
    , m_fieldOfView(45.0f)
    , m_moveSpeed(5.0f)
    , m_rotateSpeed(10.0f)
    , m_height(512)
    , m_width(512)
    , m_selectedShadingMode(0u)
    , m_mode(Mode::SELECT)
    , m_position(glm::vec3(-5.0f, 5.0f, 0.0f))
    , m_rotation(glm::vec3(-35.0f, -90.f, 0.0f))
    , m_pointerGlobalPosition(glm::vec2(0.0f, 0.0f))
    , m_texture(nullptr)
    , m_framebuffer(nullptr)
{
    SetUp();
}

SceneWindow::~SceneWindow()
{
    TearDown();
}

std::string SceneWindow::GetTitle()
{
    return "Scene";
}

void SceneWindow::OnDraw(f32 deltaTime)
{
    static const uint32 alternativeCount = 3u;
    static std::string alternatives[alternativeCount] = {
        "Shaded",
        "Wireframe",
        "Shaded Wireframe",
    };

    if (SketchCombo::Begin("Shading Combo", alternatives[m_selectedShadingMode], 200.0f))
    {
        for (uint32 i = 0u; i < alternativeCount; ++i)
        {
            if (SketchCombo::Selectable(alternatives[i], m_selectedShadingMode == i))
            {
                m_selectedShadingMode = i;
            }
        }
        SketchCombo::End();
    }

    Sketch::SameLine();
    if (Sketch::Button("Select Mode"))
    {
        m_mode = Mode::SELECT;
    }
    Sketch::SameLine();
    if (Sketch::Button("Move Mode"))
    {
        m_mode = Mode::MOVE;
    }
    Sketch::SameLine();
    if (Sketch::Button("Rotate Mode"))
    {
        m_mode = Mode::ROTATE;
    }
    Sketch::SameLine();
    if (Sketch::Button("Scale Mode"))
    {
        m_mode = Mode::SCALE;
    }
    Sketch::SameLine();
    Sketch::Checkbox("Grid", m_isGridEnabled);
    Sketch::SameLine();
    Sketch::FloatField("Speed", m_moveSpeed, 80.0f);

    DrawGizmos();

    if (!m_cameraMode)
    {
        if (SketchEvent::KeyDown(Key::Q))
        {
            m_mode = Mode::SELECT;
        }
        else if (SketchEvent::KeyDown(Key::W))
        {
            m_mode = Mode::MOVE;
        }
        else if (SketchEvent::KeyDown(Key::E))
        {
            m_mode = Mode::ROTATE;
        }
        else if (SketchEvent::KeyDown(Key::R))
        {
            m_mode = Mode::SCALE;
        }
    }

    SketchWindow::BeginChild("Scene Render Child");
    {
        glm::vec2 childSize = SketchWindow::GetSize();
        if (m_width != static_cast<int32>(childSize.x) || m_height != static_cast<int32>(childSize.y))
        {
            m_width = static_cast<int32>(childSize.x);
            m_height = static_cast<int32>(childSize.y);
            m_texture->SetData(m_width, m_height, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);
            m_depthStencil->SetData(m_width, m_height, Renderbuffer::InternalFormat::DEPTH24_STENCIL8);
        }

        if (m_isGridEnabled)
        {
            DrawGrid();
        }

        switch (m_mode)
        {
        case Mode::SELECT:
            SelectMode();
            break;
        case Mode::MOVE:
            MoveMode();
            break;
        case Mode::ROTATE:
            RotateMode();
            break;
        case Mode::SCALE:
            ScaleMode();
            break;
        default:
            break;
        }

        DrawScene(deltaTime);
    }
    SketchWindow::EndChild();
}

void SceneWindow::DrawGizmos()
{
    for (int32 i = 0; i < EditorManager::Scene()->GetSelectedTransformCount(); ++i)
    {
        Transform* transform = EditorManager::Scene()->GetSelectedTransform(i);
        std::vector<BaseComponent*> components;
        transform->GetAllComponents(components);

        for (auto c : components)
        {
            c->OnEditorGizmo();
        }
    }
}

void SceneWindow::DrawGrid()
{
    for (int32 i = -50; i <= 50; ++i)
    {
        SketchGizmo::Line(glm::vec3(static_cast<f32>(i), 0.0f, -50.0f), glm::vec3(static_cast<f32>(i), 0.0f, 50.0f), glm::vec4(0.44f, 0.44f, 0.62f, 1.0f));
    }

    for (int32 i = -50; i <= 50; ++i)
    {
        SketchGizmo::Line(glm::vec3(-50.0f, 0.0f, static_cast<f32>(i)), glm::vec3(50.0f, 0.0f, static_cast<f32>(i)), glm::vec4(0.44f, 0.44f, 0.62f, 1.0f));
    }
}

void SceneWindow::DrawScene(f32 deltaTime)
{
    if (!m_cameraMode && SketchEvent::IsPointerOverWindow() && SketchEvent::ButtonDown(Button::RIGHT))
    {
        m_cameraMode = true;
        m_pointerGlobalPosition = SketchEvent::GetPointerGlobalPosition();
    }
    else if (m_cameraMode && SketchEvent::ButtonDown(Button::RIGHT))
    {
        m_cameraMode = false;
    }

    if (m_cameraMode)
    {
        glm::vec2 pointerDelta = SketchEvent::GetPointerGlobalPosition() - m_pointerGlobalPosition;
        SketchEvent::WrapPointerGlobal(m_pointerGlobalPosition);
        SketchEvent::ShowPointer(false);

        m_rotation.x -= pointerDelta.y * m_rotateSpeed * deltaTime;
        m_rotation.x = Mathf::Clamp(-89.0f, 89.0f, m_rotation.x);
        m_rotation.y -= pointerDelta.x * m_rotateSpeed * deltaTime;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
        model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        if (SketchEvent::KeyRepeat(Key::W))
        {
            m_position -= glm::vec3(model[2]) * m_moveSpeed * deltaTime;
        }
        else if (SketchEvent::KeyRepeat(Key::S))
        {
            m_position += glm::vec3(model[2]) * m_moveSpeed * deltaTime;
        }

        if (SketchEvent::KeyRepeat(Key::A))
        {
            m_position -= glm::vec3(model[0]) * m_moveSpeed * deltaTime;
        }
        else if (SketchEvent::KeyRepeat(Key::D))
        {
            m_position += glm::vec3(model[0]) * m_moveSpeed * deltaTime;
        }
    }

    glm::mat4 projectionMatrix = glm::perspective(m_fieldOfView, static_cast<f32>(m_width) / static_cast<f32>(m_height), 0.1f, 1000.0f);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

    RenderWindow* renderWindow = Manager::Render()->GetRenderWindow();
    int32 prevViewportX = renderWindow->GetViewportX();
    int32 prevViewportY = renderWindow->GetViewportY();
    int32 prevViewportHeight = renderWindow->GetViewportHeight();
    int32 prevViewportWidth = renderWindow->GetViewportWidth();

    renderWindow->SetViewport(0, 0, m_width, m_height);
    m_framebuffer->Bind();
    {
        renderWindow->SetClearColor(glm::vec4(0.42f, 0.42f, 0.58f, 1.0f));
        renderWindow->Clear();
        glm::mat4 viewProjection = projectionMatrix * glm::inverse(model);
        Manager::Render()->RenderSceneToTexture(viewProjection);
        SketchInternal::RenderGizmos(renderWindow, viewProjection);
    }
    m_framebuffer->Unbind();
    renderWindow->SetViewport(prevViewportX, prevViewportY, prevViewportWidth, prevViewportHeight);

    Sketch::Image(m_texture, glm::vec2(m_width, m_height));
}

void SceneWindow::MoveMode()
{
    if (EditorManager::Scene()->GetSelectedTransformCount() == 1)
    {

        Transform* transform = EditorManager::Scene()->GetSelectedTransform(0);
        glm::mat4 model = transform->GetWorldMatrix();

        // Fixed distance between the camera.
        glm::vec3 position = glm::vec3(model[3]);
        f32 distance = glm::distance(position, m_position);
        glm::vec3 dir = glm::normalize(position - m_position);
        position -= dir * (distance - 8.0f);

        glm::vec4 xColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 yColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        glm::vec4 zColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        glm::vec4 xPanColor = glm::vec4(1.0f, 0.0f, 0.0f, 0.42f);
        glm::vec4 yPanColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.42f);
        glm::vec4 zPanColor = glm::vec4(0.0f, 0.0f, 1.0f, 0.42f);

        glm::vec3 xAabbMin = glm::vec3(0.0f, -0.025f, -0.025f);
        glm::vec3 xAabbMax = glm::vec3(1.0f, 0.025f, 0.025f);
        glm::vec3 xAabbMinHandle = glm::vec3(1.0f, -0.06f, -0.06f);
        glm::vec3 xAabbMaxHandle = glm::vec3(1.3f, 0.06f, 0.06f);

        glm::vec3 yAabbMin = glm::vec3(-0.025f, 0.0f, -0.025f);
        glm::vec3 yAabbMax = glm::vec3(0.025f, 1.0f, 0.025f);
        glm::vec3 yAabbMinHandle = glm::vec3(-0.06f, 1.0f, -0.06f);
        glm::vec3 yAabbMaxHandle = glm::vec3(0.06f, 1.3f, 0.06f);

        glm::vec3 zAabbMin = glm::vec3(-0.025f, -0.025f, 0.0f);
        glm::vec3 zAabbMax = glm::vec3(0.025f, 0.025f, 1.0f);
        glm::vec3 zAabbMinHandle = glm::vec3(-0.06f, -0.06f, 1.0f);
        glm::vec3 zAabbMaxHandle = glm::vec3(0.06f, 0.06f, 1.3f);

        glm::mat4 projectionMatrix = glm::perspective(m_fieldOfView, static_cast<f32>(m_width) / static_cast<f32>(m_height), 0.1f, 1000.0f);
        glm::mat4 viewInverse = glm::translate(glm::mat4(1.0f), m_position);
        viewInverse = glm::rotate(viewInverse, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        viewInverse = glm::rotate(viewInverse, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        viewInverse = glm::rotate(viewInverse, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::vec2 pointerCoords = SketchEvent::GetPointerPosition() - SketchWindow::GetPosition();
        pointerCoords.x = (2.0f * pointerCoords.x) / static_cast<f32>(m_width) - 1.0f;
        pointerCoords.y = 1.0f - (2.0f * pointerCoords.y) / static_cast<f32>(m_height);

        glm::vec4 rayClip = glm::vec4(pointerCoords.x, pointerCoords.y, -1.0f, 1.0f);
        glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
        glm::vec3 rayWorld = glm::vec3(viewInverse * rayEye);
        rayWorld = glm::normalize(rayWorld);

        Intersection::RayHitData rayHitData;
        if (Intersection::RayVsOBB(m_position, rayWorld, xAabbMin, xAabbMax, model, rayHitData) ||
            Intersection::RayVsOBB(m_position, rayWorld, xAabbMinHandle, xAabbMaxHandle, model, rayHitData))
        {
            xColor = glm::vec4(1.0f, 0.82f, 0.82f, 1.0f);
        }
        else if (Intersection::RayVsOBB(m_position, rayWorld, yAabbMin, yAabbMax, model, rayHitData) ||
            Intersection::RayVsOBB(m_position, rayWorld, yAabbMinHandle, yAabbMaxHandle, model, rayHitData))
        {
            yColor = glm::vec4(0.82f, 1.0f, 0.82f, 1.0f);
        }
        else if (Intersection::RayVsOBB(m_position, rayWorld, zAabbMin, zAabbMax, model, rayHitData) ||
            Intersection::RayVsOBB(m_position, rayWorld, zAabbMinHandle, zAabbMaxHandle, model, rayHitData))
        {
            zColor = glm::vec4(0.82f, 0.82f, 1.0f, 1.0f);
        }

        // Has to be normalized due to scaling.
        SketchGizmo::Cone(glm::normalize(glm::vec3(model[0])) + position, glm::normalize(glm::vec3(model[0])),
            glm::normalize(glm::vec3(model[1])), 0.12f, 0.25f, xColor);

        SketchGizmo::Cone(glm::normalize(glm::vec3(model[1])) + position, glm::normalize(glm::vec3(model[1])),
            glm::normalize(glm::vec3(model[2])), 0.12f, 0.25f, yColor);

        SketchGizmo::Cone(glm::normalize(glm::vec3(model[2])) + position, glm::normalize(glm::vec3(model[2])),
            glm::normalize(glm::vec3(model[0])), 0.12f, 0.25f, zColor);

        SketchGizmo::LineOverdrawn(position, glm::normalize(glm::vec3(model[0])) + position, xColor);
        SketchGizmo::LineOverdrawn(position, glm::normalize(glm::vec3(model[1])) + position, yColor);
        SketchGizmo::LineOverdrawn(position, glm::normalize(glm::vec3(model[2])) + position, zColor);

        SketchGizmo::LineOverdrawn(glm::normalize(glm::vec3(model[1])) * 0.25f + position,
            glm::normalize(glm::vec3(model[1])) * 0.25f + glm::normalize(glm::vec3(model[2])) * 0.25f + position, xPanColor);
        SketchGizmo::LineOverdrawn(glm::normalize(glm::vec3(model[2])) * 0.25f + position,
            glm::normalize(glm::vec3(model[1])) * 0.25f + glm::normalize(glm::vec3(model[2])) * 0.25f + position, xPanColor);

        SketchGizmo::LineOverdrawn(glm::normalize(glm::vec3(model[2])) * 0.25f + position,
            glm::normalize(glm::vec3(model[2])) * 0.25f + glm::normalize(glm::vec3(model[0])) * 0.25f + position, yPanColor);
        SketchGizmo::LineOverdrawn(glm::normalize(glm::vec3(model[0])) * 0.25f + position,
            glm::normalize(glm::vec3(model[2])) * 0.25f + glm::normalize(glm::vec3(model[0])) * 0.25f + position, yPanColor);

        SketchGizmo::LineOverdrawn(glm::normalize(glm::vec3(model[0])) * 0.25f + position,
            glm::normalize(glm::vec3(model[0])) * 0.25f + glm::normalize(glm::vec3(model[1])) * 0.25f + position, zPanColor);
        SketchGizmo::LineOverdrawn(glm::normalize(glm::vec3(model[1])) * 0.25f + position,
            glm::normalize(glm::vec3(model[0])) * 0.25f + glm::normalize(glm::vec3(model[1])) * 0.25f + position, zPanColor);
    }
}

void SceneWindow::RotateMode()
{
    if (EditorManager::Scene()->GetSelectedTransformCount() == 1)
    {
        Transform* transform = EditorManager::Scene()->GetSelectedTransform(0);
        glm::mat4 model = transform->GetWorldMatrix();
        model[0] = glm::vec4(glm::normalize(glm::vec3(model[0])), model[0][3]);
        model[1] = glm::vec4(glm::normalize(glm::vec3(model[1])), model[1][3]);
        model[2] = glm::vec4(glm::normalize(glm::vec3(model[2])), model[2][3]);
        glm::vec3 center = model[3];

        glm::vec4 xColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 yColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        glm::vec4 zColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        glm::mat4 projectionMatrix = glm::perspective(m_fieldOfView, static_cast<f32>(m_width) / static_cast<f32>(m_height), 0.1f, 1000.0f);
        glm::mat4 viewInverse = glm::translate(glm::mat4(1.0f), m_position);
        viewInverse = glm::rotate(viewInverse, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        viewInverse = glm::rotate(viewInverse, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        viewInverse = glm::rotate(viewInverse, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::vec2 pointerCoords = SketchEvent::GetPointerPosition() - SketchWindow::GetPosition();
        pointerCoords.x = (2.0f * pointerCoords.x) / static_cast<f32>(m_width) - 1.0f;
        pointerCoords.y = 1.0f - (2.0f * pointerCoords.y) / static_cast<f32>(m_height);

        glm::vec4 rayClip = glm::vec4(pointerCoords.x, pointerCoords.y, -1.0f, 1.0f);
        glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
        glm::vec3 rayWorld = glm::vec3(viewInverse * rayEye);
        rayWorld = glm::normalize(rayWorld);

        Intersection::RayHitData rayHitData;
        if (Intersection::RayVsSphere(m_position, rayWorld, center, 1.0f, rayHitData))
        {
            glm::vec3 maxNormal = glm::normalize((m_position + rayHitData.tMax * rayWorld) - center);

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

void SceneWindow::ScaleMode()
{
    if (EditorManager::Scene()->GetSelectedTransformCount() == 1)
    {
        Transform* transform = EditorManager::Scene()->GetSelectedTransform(0);
        glm::vec3 position = transform->GetWorldPosition();
        glm::mat3 model = glm::mat3(transform->GetWorldMatrix());

        // Has to be normalized due to scaling.
        SketchGizmo::LineOverdrawn(position, glm::normalize(model[0]) + position, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        SketchGizmo::LineOverdrawn(position, glm::normalize(model[1]) + position, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        SketchGizmo::LineOverdrawn(position, glm::normalize(model[2]) + position, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    }
}

void SceneWindow::SelectMode()
{
    if (!m_cameraMode && SketchEvent::IsPointerOverWindow() && SketchEvent::ButtonDown(Button::LEFT))
    {
        glm::mat4 projectionMatrix = glm::perspective(m_fieldOfView, static_cast<f32>(m_width) / static_cast<f32>(m_height), 0.1f, 1000.0f);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
        model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        // To nds.
        glm::vec2 pointerCoords = SketchEvent::GetPointerPosition() - SketchWindow::GetPosition();
        pointerCoords.x = (2.0f * pointerCoords.x) / static_cast<f32>(m_width) - 1.0f;
        pointerCoords.y = 1.0f - (2.0f * pointerCoords.y) / static_cast<f32>(m_height);

        glm::vec4 rayClip = glm::vec4(pointerCoords.x, pointerCoords.y, -1.0f, 1.0f);
        glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
        glm::vec3 rayWorld = glm::vec3(model * rayEye);
        rayWorld = glm::normalize(rayWorld);

        Transform* transform = Manager::Render()->PickMesh(m_position, rayWorld);
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

void SceneWindow::SetUp()
{
    m_framebuffer = new Framebuffer();

    m_texture = new Texture();
    m_texture->SetData(m_width, m_height, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);
    m_framebuffer->AttachTexture(0, m_texture);

    m_depthStencil = new Renderbuffer();
    m_depthStencil->SetData(m_width, m_height, Renderbuffer::InternalFormat::DEPTH24_STENCIL8);
    m_framebuffer->AttachDepthStencil(m_depthStencil);
}

void SceneWindow::TearDown()
{
    delete m_texture;
    m_texture = nullptr;
    delete m_depthStencil;
    m_depthStencil = nullptr;
    delete m_framebuffer;
    m_framebuffer = nullptr;
}
} // namespace spy
