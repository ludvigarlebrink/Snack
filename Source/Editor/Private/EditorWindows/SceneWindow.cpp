#include "EditorWindows/SceneWindow.hpp"
#include "EditorManager.hpp"
#include "EngineInclude.hpp"
#include "UtilsInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"
#include "SketchInternal.hpp"
#include "SceneTools/SceneMoveTool.hpp"
#include "SceneTools/SceneRotateTool.hpp"
#include "SceneTools/SceneScaleTool.hpp"
#include "SceneTools/SceneSelectTool.hpp"
#include "SceneTools/SceneToolData.hpp"

#include <string>

namespace snack
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

    if (SketchCombo::Begin("##Shading Combo", alternatives[m_selectedShadingMode], 200.0f))
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
    if (Sketch::ImageButton(m_selectToolIcon, false))
    {
        m_activeSceneTool->OnEnd();
        m_activeSceneTool = m_selectTool;
        m_activeSceneTool->OnBegin();
    }
    Sketch::SameLine();
    if (Sketch::ImageButton(m_moveToolIcon, false))
    {
        m_activeSceneTool->OnEnd();
        m_activeSceneTool = m_moveTool;
        m_activeSceneTool->OnBegin();
    }
    Sketch::SameLine();
    if (Sketch::ImageButton(m_rotateToolIcon, false))
    {
        m_activeSceneTool->OnEnd();
        m_activeSceneTool = m_rotateTool;
        m_activeSceneTool->OnBegin();
    }
    Sketch::SameLine();
    if (Sketch::ImageButton(m_scaleToolIcon, false))
    {
        m_activeSceneTool->OnEnd();
        m_activeSceneTool = m_scaleTool;
        m_activeSceneTool->OnBegin();
    }
    Sketch::SameLine();
    Sketch::Checkbox("Grid", m_isGridEnabled);
    Sketch::SameLine();
    Sketch::FloatField("Speed", m_moveSpeed, 80.0f);

    if (SketchWindow::IsFocused())
    {
        // Delete
        if (SketchEvent::KeyDown(Key::DELETE))
        {
            EditorManager::Scene()->DeleteSelectedTransforms();
        }
        
        // Copy.
        if (SketchEvent::KeyDown(Key::C, Mod::CTRL))
        {
            EditorManager::Scene()->CopySelectedTransforms();
        }

        // Paste.
        if (SketchEvent::KeyDown(Key::V, Mod::CTRL))
        {
            EditorManager::Scene()->PasteTransforms();
        }

        // Duplicate.
        if (SketchEvent::KeyDown(Key::D, Mod::CTRL))
        {
            EditorManager::Scene()->DuplicateSelectedTransforms();
        }

        if (!m_cameraMode)
        {
            if (SketchEvent::KeyDown(Key::Q))
            {
                m_activeSceneTool->OnEnd();
                m_activeSceneTool = m_selectTool;
                m_activeSceneTool->OnBegin();
            }
            else if (SketchEvent::KeyDown(Key::W))
            {
                m_activeSceneTool->OnEnd();
                m_activeSceneTool = m_moveTool;
                m_activeSceneTool->OnBegin();
            }
            else if (SketchEvent::KeyDown(Key::E))
            {
                m_activeSceneTool->OnEnd();
                m_activeSceneTool = m_rotateTool;
                m_activeSceneTool->OnBegin();
            }
            else if (SketchEvent::KeyDown(Key::R))
            {
                m_activeSceneTool->OnEnd();
                m_activeSceneTool = m_scaleTool;
                m_activeSceneTool->OnBegin();
            }
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

        if (!m_cameraMode && SketchEvent::IsPointerOverWindow() && SketchEvent::ButtonDown(Button::RIGHT))
        {
            m_cameraMode = true;
            m_pointerGlobalPosition = SketchEvent::GetPointerGlobalPosition();
        }
        else if (m_cameraMode && SketchEvent::ButtonDown(Button::RIGHT))
        {
            m_cameraMode = false;
        }

        glm::mat4 projection = glm::perspective(m_fieldOfView, static_cast<f32>(m_width) / static_cast<f32>(m_height), 0.1f, 1000.0f);
        glm::mat4 viewInverse = glm::translate(glm::mat4(1.0f), m_position);
        viewInverse = glm::rotate(viewInverse, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        viewInverse = glm::rotate(viewInverse, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        viewInverse = glm::rotate(viewInverse, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        if (m_cameraMode)
        {
            glm::vec2 pointerDelta = SketchEvent::GetPointerGlobalPosition() - m_pointerGlobalPosition;
            SketchEvent::WrapPointerGlobal(m_pointerGlobalPosition);
            SketchEvent::ShowPointer(false);

            m_rotation.x -= pointerDelta.y * m_rotateSpeed * deltaTime;
            m_rotation.x = Mathf::Clamp(-89.0f, 89.0f, m_rotation.x);
            m_rotation.y -= pointerDelta.x * m_rotateSpeed * deltaTime;

            if (SketchEvent::KeyRepeat(Key::W))
            {
                m_position -= glm::vec3(viewInverse[2]) * m_moveSpeed * deltaTime;
            }
            else if (SketchEvent::KeyRepeat(Key::S))
            {
                m_position += glm::vec3(viewInverse[2]) * m_moveSpeed * deltaTime;
            }

            if (SketchEvent::KeyRepeat(Key::A))
            {
                m_position -= glm::vec3(viewInverse[0]) * m_moveSpeed * deltaTime;
            }
            else if (SketchEvent::KeyRepeat(Key::D))
            {
                m_position += glm::vec3(viewInverse[0]) * m_moveSpeed * deltaTime;
            }
        }

        if (m_isGridEnabled)
        {
            DrawGrid();
        }

        SceneToolData data;
        data.cameraMode = m_cameraMode;
        data.cameraPosition = m_position;
        data.height = m_height;
        data.width = m_width;
        data.viewInverse = viewInverse;
        data.projection = projection;

        m_activeSceneTool->OnTick(data);

        DrawGizmos();
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
        Manager::Render()->RenderSceneCustomCamera(viewProjection);
        SketchInternal::RenderGizmos(renderWindow, viewProjection);
    }
    m_framebuffer->Unbind();
    renderWindow->SetViewport(prevViewportX, prevViewportY, prevViewportWidth, prevViewportHeight);

    Sketch::Image(m_texture, glm::vec2(m_width, m_height));
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

    // Setup tools.
    m_moveTool = new SceneMoveTool();
    m_rotateTool = new SceneRotateTool();
    m_scaleTool = new SceneScaleTool();
    m_selectTool = new SceneSelectTool();
    m_activeSceneTool = m_selectTool;

    // @todo Set correct path.
    m_selectToolIcon = new Texture();
    m_selectToolIcon->LoadFromFile("EditorData/Icons/SelectToolIcon_32.png", Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE);
    m_moveToolIcon = new Texture();
    m_moveToolIcon->LoadFromFile("EditorData/Icons/SelectToolIcon_32.png", Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE);
    m_rotateToolIcon = new Texture();
    m_rotateToolIcon->LoadFromFile("EditorData/Icons/SelectToolIcon_32.png", Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE);
    m_scaleToolIcon = new Texture();
    m_scaleToolIcon->LoadFromFile("EditorData/Icons/SelectToolIcon_32.png", Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE);
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
} // namespace snack
