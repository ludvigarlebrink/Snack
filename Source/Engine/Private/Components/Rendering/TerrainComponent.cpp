#include "Components/Rendering/TerrainComponent.hpp"
#include "Manager.hpp"
#ifdef SPY_EDITOR
#include "SketchInclude.hpp"
#endif
#include "UtilsInclude.hpp"

namespace snack
{
TerrainComponent::TerrainComponent(Transform* transform)
    : BaseComponent(transform)
    , m_terrain(nullptr)
{
    Manager::Render()->RegisterTerrainComponent(this);
}

TerrainComponent::~TerrainComponent()
{
    if (m_terrain)
    {
        Manager::Asset()->DestroyTerrain(m_filepath);
    }

    Manager::Render()->DeregisterTerrainComponent(this);
}

std::string TerrainComponent::GetComponentID()
{
    return CLASS_NAME(TerrainComponent);
}

Terrain* TerrainComponent::GetTerrain()
{
    return m_terrain;
}

void TerrainComponent::Load(cereal::JSONInputArchive& archive)
{
    BaseComponent::Load(archive);
}

#ifdef SPY_EDITOR
void TerrainComponent::OnEditorInspector()
{
    Sketch::TextField("Terrain", m_filepath);

    std::string filepath = "";
    if (SketchDragDrop::TextTarget("Filename", filepath))
    {
        if (filepath.substr(filepath.find_last_of('.')) == ".trn")
        {
            if (m_terrain)
            {
                Manager::Asset()->DestroyTerrain(m_filepath);
            }

            m_terrain = Manager::Asset()->LoadTerrain(filepath);
            if (m_terrain)
            {
                m_filepath = filepath;
            }
        }
    }
}
#endif

void TerrainComponent::Save(cereal::JSONOutputArchive& archive)
{
    BaseComponent::Save(archive);
}

void TerrainComponent::SetTerrain(const std::string& filepath)
{
}
} // namespace snack
