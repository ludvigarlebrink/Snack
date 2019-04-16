#pragma once

#include "Managers/IAssetManager.hpp"

#include <string>
#include <unordered_map>

namespace snack
{
class ENGINE_API AssetManager final : public IAssetManager
{
public:

    AssetManager();

    ~AssetManager();

    void DestroyTerrain(const std::string& filepath) override;

    void DestroyTexture(const std::string& filepath) override;

    Material* GetDefaultMaterial() override;

    Material* LoadMaterial(const std::string& filepath) override;

    Terrain* LoadTerrain(const std::string& filepath) override;

    Texture* LoadTexture(const std::string& filepath) override;

private:

    std::unordered_map<std::string, std::pair<int32, Material*>> m_materials;
    std::unordered_map<std::string, std::pair<int32, Terrain*>> m_terrains;
    std::unordered_map<std::string, std::pair<int32, Texture*>> m_textures;
    Material* m_defaultMaterial;
};
} // namespace snack
