#pragma once

#include "Components/BaseComponent.hpp"

#include <string>

namespace snack
{
class Terrain;

class ENGINE_API TerrainComponent final : public BaseComponent
{
public:

    TerrainComponent(Transform* transform);

    ~TerrainComponent();

    std::string GetComponentID() override;

    Terrain* GetTerrain();

#ifdef SPY_EDITOR
    void OnEditorInspector() override;
#endif

    void SetTerrain(const std::string& filename);

private:

    Terrain* m_terrain;
    std::string m_filename;
};
} // namespace snack
