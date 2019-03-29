#include "EditorWindows\ShaderEditorWindow.hpp"
#include "SketchInclude.hpp"

namespace spy
{
ShaderEditorWindow::ShaderEditorWindow()
{
}

ShaderEditorWindow::~ShaderEditorWindow()
{
}

std::string ShaderEditorWindow::GetTitle()
{
    return "Shader Editor";
}

void ShaderEditorWindow::OnDraw(f32 deltaTime)
{
    SketchNode::Begin(1353);
}
} // namespace spy
