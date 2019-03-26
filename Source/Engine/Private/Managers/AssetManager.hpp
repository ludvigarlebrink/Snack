#pragma once

#include "Managers/IAssetManager.hpp"

#include <string>
#include <unordered_map>

namespace spy
{
class ENGINE_API AssetManager final : public IAssetManager
{
public:

    AssetManager();

    ~AssetManager();

    void DestroyTexture(const std::string& filename) override;

    Texture* LoadTexture(const std::string& filename) override;

private:

    std::unordered_map<std::string, std::pair<int32, Texture*>> m_textures;
};
} // namespace spy
