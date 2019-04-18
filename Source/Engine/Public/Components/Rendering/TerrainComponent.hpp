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

    void Load(cereal::JSONInputArchive& archive) override;

#ifdef SPY_EDITOR
    void OnEditorInspector() override;
#endif

    void Save(cereal::JSONOutputArchive& archive) override;

    void SetTerrain(const std::string& filepath);

private:

    Terrain* m_terrain;
    std::string m_filepath;
};
} // namespace snack
