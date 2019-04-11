#pragma once

#include "EditorWindow.hpp"

namespace snack
{
class EDITOR_API ScriptEditorWindow final : public EditorWindow
{
public:

    ScriptEditorWindow();

    ~ScriptEditorWindow();

    std::string GetTitle() override;

protected:

    void OnDraw(f32 deltaTime) override;
};
} // namespace snack
