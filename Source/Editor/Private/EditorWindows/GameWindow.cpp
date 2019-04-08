#include "EditorWindows/GameWindow.hpp"
#include "EngineInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

namespace spy
{
GameWindow::GameWindow()
    : m_texture(nullptr)
    , m_framebuffer(nullptr)
{
    SetUp();
}

GameWindow::~GameWindow()
{
    TearDown();
}

std::string GameWindow::GetTitle()
{
    return "Game";
}

void GameWindow::OnDraw(f32 deltaTime)
{
    Sketch::Button("Begin Play");
    Sketch::SameLine();
    Sketch::Button("Pause Play");

    SketchWindow::BeginChild("Scene Render Child");
    {
        glm::vec2 childSize = SketchWindow::GetSize();
        if (m_texture->GetWidth() != static_cast<int32>(childSize.x) ||
            m_texture->GetHeight() != static_cast<int32>(childSize.y))
        {
            int32 width = static_cast<int32>(childSize.x);
            int32 height = static_cast<int32>(childSize.y);
            m_texture->SetData(width, height, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);
        }

        glm::vec2 windowSize = SketchWindow::GetSize();
        Manager::Render()->RenderSceneToTexture(m_framebuffer, windowSize.x, windowSize.y);
        Sketch::Image(m_texture, glm::vec2(m_texture->GetWidth(), m_texture->GetHeight()));
    }
    SketchWindow::EndChild();
}

void GameWindow::SetUp()
{
    m_texture = new Texture();
    m_texture->SetData(512, 512, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);

    m_framebuffer = new Framebuffer();
    m_framebuffer->AttachTexture(0, m_texture);
}

void GameWindow::TearDown()
{
    delete m_texture;
    m_texture = nullptr;
    delete m_framebuffer;
    m_framebuffer = nullptr;
}
} // namespace spy
