#pragma once

#include "BaseTypes.hpp"
#include "RenderCoreForward.hpp"
#include "Mesh.hpp"
#include "Material.hpp"

#include <string>

namespace spy
{
class ENGINE_API IAssetManager
{
public:

    virtual ~IAssetManager() = default;

    virtual void DestroyTexture(const std::string& filename) = 0;

    virtual Material* GetDefaultMaterial() = 0;

    virtual Material* LoadMaterial(const std::string& filename) = 0;

    virtual Texture* LoadTexture(const std::string& filename) = 0;
};
} // namespace spy
