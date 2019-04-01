#pragma once

#include "BaseTypes.hpp"
#include "Mesh.hpp"
#include "RenderCoreForward.hpp"

#include <string>

namespace spy
{
class Material;

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
