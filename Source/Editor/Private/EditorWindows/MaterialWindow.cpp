#include"EditorWindows/MaterialWindow.hpp"
#include "EngineInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

namespace spy
{
MaterialWindow::MaterialWindow()
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
}

void MaterialWindow::TearDown()
{
}
} // namespace spy
