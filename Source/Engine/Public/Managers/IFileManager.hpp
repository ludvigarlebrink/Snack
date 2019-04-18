#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace snack
{
class IFileManager
{
public:

    virtual ~IFileManager() = default;

    virtual bool GetAllPrefabNames(std::vector<std::string>& prefabNames) = 0;

    virtual bool GetAllSceneNames(std::vector<std::string>& sceneNames) = 0;

    virtual bool GetAllScriptNames(std::vector<std::string>& scriptNames) = 0;

    virtual bool GetAllTerrainNames(std::vector<std::string>& terrainNames) = 0;

    virtual bool GetAllTextureNames(std::vector<std::string>& textureNames) = 0;

    virtual bool GetPrefabPath(const std::string& filename, std::string& filepath) = 0;

    virtual bool GetScenePath(const std::string& filename, std::string& filepath) = 0;

    virtual bool GetScriptPath(const std::string& filename, std::string& filepath) = 0;

    virtual bool GetTerrainPath(const std::string& filename, std::string& filepath) = 0;

    virtual bool GetTexturePath(const std::string& filename, std::string& filepath) = 0;

    virtual void Refresh() = 0;
};
} // namespace snack
