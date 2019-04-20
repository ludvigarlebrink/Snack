#include "EditorWindows\ScriptEditorWindow.hpp"
#include "EngineInclude.hpp"
#include "SketchInclude.hpp"

namespace snack
{
ScriptEditorWindow::ScriptEditorWindow()
{
    SetUp();
}

ScriptEditorWindow::~ScriptEditorWindow()
{
    TearDown();
}

std::string ScriptEditorWindow::GetTitle()
{
    return "Script Editor";
}

void ScriptEditorWindow::OpenScript(const std::string& filename)
{
    std::string filepath = "";
    if (Manager::File()->GetScriptPath(filename, filepath))
    {
        std::ifstream f(filepath);
        if (f.is_open())
        {
            std::string source((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
            f.close();
            m_textEditor->SetText(source);
        }
    }
}

void ScriptEditorWindow::OnDraw(f32 deltaTime)
{
    Sketch::Button("Save");
    Sketch::SameLine();
    Sketch::Button("Debug");

    m_textEditor->Render("Some Script");
}

void ScriptEditorWindow::SetUp()
{
    m_textEditor = new SketchTextEditor();
    auto lang = SketchTextEditor::LanguageDefinition::Lua();
    m_textEditor->SetLanguageDefinition(lang);
}

void ScriptEditorWindow::TearDown()
{
    delete m_textEditor;
}
} // namespace snack
