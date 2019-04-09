#pragma once

#include "EditorWindow.hpp"
#include "RenderCoreForward.hpp"

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

    void SetUp();

    void TearDown();

private:

    Texture* m_elevationBrushIcon;
    Texture* m_paintBrushIcon;
};
} // namespace snack
