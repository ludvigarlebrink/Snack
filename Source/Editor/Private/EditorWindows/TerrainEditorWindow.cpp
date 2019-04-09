#include "EditorWindows/TerrainEditorWindow.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

namespace snack
{
TerrainEditorWindow::TerrainEditorWindow()
    : m_elevationBrushIcon(nullptr)
    , m_paintBrushIcon(nullptr)
{
    SetUp();
}

TerrainEditorWindow::~TerrainEditorWindow()
{
    TearDown();
}

std::string TerrainEditorWindow::GetTitle()
{
    return "Terrain Editor";
}

void TerrainEditorWindow::OnDraw(f32 deltaTime)
{
    Sketch::ImageButton(m_elevationBrushIcon, false, glm::vec4(0.8f, 0.8f, 1.0f, 1.0f));
    Sketch::SameLine();
    Sketch::ImageButton(m_paintBrushIcon, false, glm::vec4(0.8f, 0.8f, 1.0f, 1.0f));
}

void TerrainEditorWindow::SetUp()
{
    // @todo Set correct path.
    m_elevationBrushIcon = new Texture();
    m_elevationBrushIcon->LoadFromFile("EditorData/Icons/TerrainElevationBrush_64.png", Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE);

    m_paintBrushIcon = new Texture();
    m_paintBrushIcon->LoadFromFile("EditorData/Icons/TerrainPaintBrush_64.png", Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE);
}

void TerrainEditorWindow::TearDown()
{
    delete m_elevationBrushIcon;
    delete m_paintBrushIcon;
}
} // namespace snack
