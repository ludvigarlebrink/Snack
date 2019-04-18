#pragma once

#include "Managers/IFileManager.hpp"

#include <unordered_map>

namespace snack
{
class FileManager final : public IFileManager
{
public:

    FileManager();

    ~FileManager();

    bool GetAllPrefabNames(std::vector<std::string>& prefabNames) override;

    bool GetAllSceneNames(std::vector<std::string>& sceneNames) override;

    bool GetAllScriptNames(std::vector<std::string>& scriptNames) override;

    bool GetAllTerrainNames(std::vector<std::string>& terrainNames) override;

    bool GetAllTextureNames(std::vector<std::string>& textureNames) override;

    bool GetPrefabPath(const std::string& filename, std::string& filepath) override;

    bool GetScenePath(const std::string& filename, std::string& filepath) override;

    bool GetScriptPath(const std::string& filename, std::string& filepath) override;

    bool GetTerrainPath(const std::string& filename, std::string& filepath) override;

    bool GetTexturePath(const std::string& filename, std::string& filepath) override;

    void Refresh() override;

private:

    void SetUp();

    void TearDown();

private:

    std::unordered_map<std::string, std::string> m_prefabs;
    std::unordered_map<std::string, std::string> m_scenes;
    std::unordered_map<std::string, std::string> m_scripts;
    std::unordered_map<std::string, std::string> m_terrains;
    std::unordered_map<std::string, std::string> m_textures;
};
} // namespace snack
