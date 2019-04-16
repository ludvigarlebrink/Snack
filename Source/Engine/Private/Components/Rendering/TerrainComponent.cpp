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
        Manager::Asset()->DestroyTerrain(m_filename);
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
    Sketch::TextField("Terrain", m_filename);
    if (SketchDragDrop::BeginTarget())
    {
        SketchDragDrop::Payload payload;
        if (SketchDragDrop::AcceptPayload("Filename", payload))
        {
            std::string filepath = static_cast<char*>(payload.data);

            if (filepath.substr(filepath.find_last_of('.')) == ".trn")
            {
                if (m_terrain)
                {
                    Manager::Asset()->DestroyTerrain(m_filename);
                }

                m_terrain = Manager::Asset()->LoadTerrain(filepath);
                if (m_terrain)
                {
                    m_filename = filepath;
                }
            }
        }
        SketchDragDrop::EndTarget();
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
