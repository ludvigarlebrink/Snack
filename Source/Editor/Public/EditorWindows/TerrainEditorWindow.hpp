#pragma once

#include "EditorWindow.hpp"
#include "EngineForward.hpp"
#include "RenderCoreForward.hpp"

namespace snack
{
class EDITOR_API TerrainEditorWindow : public EditorWindow
{
public:

    TerrainEditorWindow();

    ~TerrainEditorWindow();

    std::string GetTitle() override;

    void SetTerrain(const std::string& filepath);

protected:

    void OnDraw(f32 deltaTime) override;

private:

    void SetUp();

    void TearDown();

private:

    Terrain* m_terrain;
    Texture* m_elevationBrushIcon;
    Texture* m_paintBrushIcon;

    std::string m_filename;
};
} // namespace snack
