#include"EditorWindows/MaterialEditorWindow.hpp"
#include "EngineInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

namespace spy
{
MaterialEditorWindow::MaterialEditorWindow()
{
    SetUp();
}

MaterialEditorWindow::~MaterialEditorWindow()
{
    TearDown();
}

std::string MaterialEditorWindow::GetTitle()
{
    return "Material Editor";
}

void MaterialEditorWindow::OnDraw(f32 deltaTime)
{
}

void MaterialEditorWindow::SetUp()
{
}

void MaterialEditorWindow::TearDown()
{
}
} // namespace spy
