#pragma once

#include "EditorWindow.hpp"

namespace spy
{
class EDITOR_API ShaderEditorWindow final : public EditorWindow
{
public:

    ShaderEditorWindow();

    ~ShaderEditorWindow();

    std::string GetTitle() override;

    void OnDraw(f32 deltaTime) override;

private:


};
} // namespace spy
