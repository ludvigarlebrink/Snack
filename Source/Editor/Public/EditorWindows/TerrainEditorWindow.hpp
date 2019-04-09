#pragma once

#include "EditorWindow.hpp"

namespace snack
{
class EDITOR_API TerrainEditorWindow : public EditorWindow
{
public:

    TerrainEditorWindow();

    ~TerrainEditorWindow();

    std::string GetTitle() override;

protected:

    void OnDraw(f32 deltaTime) override;

private:


};
} // namespace snack
