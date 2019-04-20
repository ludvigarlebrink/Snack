#pragma once

#include "EditorWindow.hpp"
#include "SketchForward.hpp"

namespace snack
{
class EDITOR_API ScriptEditorWindow final : public EditorWindow
{
public:

    ScriptEditorWindow();

    ~ScriptEditorWindow();

    std::string GetTitle() override;

    void OpenScript(const std::string& filename);

protected:

    void OnDraw(f32 deltaTime) override;

private:

    void SetUp();

    void TearDown();

private:

    SketchTextEditor* m_textEditor;
};
} // namespace snack
