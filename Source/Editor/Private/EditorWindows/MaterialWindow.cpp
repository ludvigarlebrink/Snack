#include"EditorWindows/MaterialWindow.hpp"
#include "EngineInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

namespace spy
{
    MaterialWindow::MaterialWindow()
        : m_height(50)
        , m_width(50)
        , m_texture(nullptr)
        , m_framebuffer(nullptr)
    {
        SetUp();
    }

    MaterialWindow::~MaterialWindow()
    {
        TearDown();
    }

    std::string MaterialWindow::GetTitle()
    {
        return "Material";
    }

    void MaterialWindow::OnDraw(f32 deltaTime)
    {
        Sketch::Button("Materials");
    }

    void MaterialWindow::SetUp()
    {
        m_texture = new Texture();
        m_texture->SetData(m_width, m_height, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, nullptr);

        m_framebuffer = new Framebuffer();
        m_framebuffer->AttachTexture(0, m_texture);
    }

    void MaterialWindow::TearDown()
    {
        delete m_texture;
        m_texture = nullptr;
        delete m_framebuffer;
        m_framebuffer = nullptr;
    }
}

