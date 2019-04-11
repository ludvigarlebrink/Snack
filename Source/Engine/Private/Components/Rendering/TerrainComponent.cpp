#include "Components/Rendering/TerrainComponent.hpp"
#include "Manager.hpp"
#ifdef SPY_EDITOR
#include "SketchInclude.hpp"
#endif

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
    return typeid(TerrainComponent).name();
}

Terrain* TerrainComponent::GetTerrain()
{
    return m_terrain;
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
            std::string filename = static_cast<char*>(payload.data);

            if (filename.substr(filename.find_last_of('.')) == ".terrain")
            {
                if (m_terrain)
                {
                    Manager::Asset()->DestroyTerrain(m_filename);
                }

                m_terrain = Manager::Asset()->LoadTerrain(filename);
                if (m_terrain)
                {
                    m_filename = filename;
                }
            }
        }
        SketchDragDrop::EndTarget();
    }
}
#endif

void TerrainComponent::SetTerrain(const std::string& filename)
{
}
} // namespace snack
