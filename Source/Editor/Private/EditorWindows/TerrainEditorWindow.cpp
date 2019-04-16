#include "EditorWindows/TerrainEditorWindow.hpp"
#include "EngineInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

namespace snack
{
TerrainEditorWindow::TerrainEditorWindow()
    : m_terrain(nullptr)
    , m_elevationBrushIcon(nullptr)
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

void TerrainEditorWindow::SetTerrain(const std::string& filepath)
{
    if (m_terrain)
    {
        Manager::Asset()->DestroyTerrain(filepath);
    }

    m_terrain = Manager::Asset()->LoadTerrain(filepath);
    m_filename = filepath;
}

void TerrainEditorWindow::OnDraw(f32 deltaTime)
{
    if (!m_terrain)
    {
        return;
    }

    Sketch::ImageButton(m_elevationBrushIcon, false, glm::vec4(0.8f, 0.8f, 1.0f, 1.0f));
    Sketch::SameLine();
    Sketch::ImageButton(m_paintBrushIcon, false, glm::vec4(0.8f, 0.8f, 1.0f, 1.0f));

    int32 width = m_terrain->GetSize();
    if (Sketch::IntField("Size", width))
    {
        m_terrain->SetSize(width);
    }

    if (Sketch::Button("Save"))
    {
        m_terrain->Save(m_filename);
    }
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
