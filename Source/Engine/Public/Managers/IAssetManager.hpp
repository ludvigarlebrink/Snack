#pragma once

#include "BaseTypes.hpp"
#include "Mesh.hpp"
#include "RenderCoreForward.hpp"

#include <string>

namespace snack
{
class Material;
class Terrain;

class ENGINE_API IAssetManager
{
public:

    virtual ~IAssetManager() = default;

    virtual void DestroyTerrain(const std::string& filename) = 0;

    virtual void DestroyTexture(const std::string& filename) = 0;

    virtual Material* GetDefaultMaterial() = 0;

    virtual Material* LoadMaterial(const std::string& filename) = 0;

    virtual Terrain* LoadTerrain(const std::string& filename) = 0;

    virtual Texture* LoadTexture(const std::string& filename) = 0;
};
} // namespace snack
