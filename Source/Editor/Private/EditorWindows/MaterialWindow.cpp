#include "EditorWindows/MaterialWindow.hpp"
#include "EngineInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

namespace spy
{
MaterialWindow::MaterialWindow()
    : m_material(nullptr)
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
    glm::vec4 color(0.00,0.00,0.00,0.00);
    glm::vec4 texture(0.00, 0.00, 0.00, 0.00);
    Sketch::Vec4Field("Color",color);
    if (m_material)
    {
        m_material->SetColor("Test", color);
    }
    //test.SetColor
    Sketch::Vec4Field("Texture",texture);
}

void MaterialWindow::SetUp()
{
  
}

void MaterialWindow::TearDown()
{
    //delete m_texture;
    //m_texture = nullptr;
    //delete m_framebuffer;
    //m_framebuffer = nullptr;
}
} // namespace spy
