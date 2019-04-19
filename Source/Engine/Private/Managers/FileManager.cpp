#include "FileManager.hpp"
#include "PlatformInclude.hpp"

namespace snack
{
FileManager::FileManager()
{
    SetUp();
}

FileManager::~FileManager()
{
    TearDown();
}

bool FileManager::GetAllPrefabNames(std::vector<std::string>& prefabNames)
{
    if (m_prefabs.empty())
    {
        return false;
    }

    for (auto i : m_prefabs)
    {
        prefabNames.push_back(i.first);
    }

    return true;
}

bool FileManager::GetAllSceneNames(std::vector<std::string>& sceneNames)
{
    if (m_scenes.empty())
    {
        return false;
    }

    for (auto i : m_scenes)
    {
        sceneNames.push_back(i.first);
    }

    return true;
}

bool FileManager::GetAllScriptNames(std::vector<std::string>& scriptNames)
{
    if (m_scripts.empty())
    {
        return false;
    }

    for (auto i : m_scripts)
    {
        scriptNames.push_back(i.first);
    }

    return true;
}

bool FileManager::GetAllTerrainNames(std::vector<std::string>& terrainNames)
{
    if (m_terrains.empty())
    {
        return false;
    }

    for (auto i : m_terrains)
    {
        terrainNames.push_back(i.first);
    }

    return true;
}

bool FileManager::GetAllTextureNames(std::vector<std::string>& textureNames)
{
    if (m_textures.empty())
    {
        return false;
    }

    for (auto i : m_textures)
    {
        textureNames.push_back(i.first);
    }

    return true;
}

bool FileManager::GetPrefabPath(const std::string& filename, std::string& filepath)
{
    auto itr = m_prefabs.find(filename);
    if (itr != m_prefabs.end())
    {
        filepath = itr->second;
        return true;
    }

    return false;
}

bool FileManager::GetScenePath(const std::string& filename, std::string& filepath)
{
    auto itr = m_scenes.find(filename);
    if (itr != m_scenes.end())
    {
        filepath = itr->second;
        return true;
    }

    return false;
}

bool FileManager::GetScriptPath(const std::string& filename, std::string& filepath)
{
    auto itr = m_scripts.find(filename);
    if (itr != m_scripts.end())
    {
        filepath = itr->second;
        return true;
    }

    return false;
}

bool FileManager::GetTerrainPath(const std::string& filename, std::string& filepath)
{
    auto itr = m_terrains.find(filename);
    if (itr != m_terrains.end())
    {
        filepath = itr->second;
        return true;
    }

    return false;
}

bool FileManager::GetTexturePath(const std::string& filename, std::string& filepath)
{
    auto itr = m_textures.find(filename);
    if (itr != m_textures.end())
    {
        filepath = itr->second;
        return true;
    }

    return false;
}

bool FileManager::PrefabExists(const std::string& filename)
{
    auto itr = m_prefabs.find(filename);
    if (itr != m_prefabs.end())
    {
        return true;
    }

    return false;
}

bool FileManager::SceneExists(const std::string& filename)
{
    auto itr = m_scenes.find(filename);
    if (itr != m_scenes.end())
    {
        return true;
    }

    return false;
}

bool FileManager::ScriptExists(const std::string& filename)
{
    auto itr = m_scripts.find(filename);
    if (itr != m_scripts.end())
    {
        return true;
    }

    return false;
}

bool FileManager::TerrainExists(const std::string& filename)
{
    auto itr = m_terrains.find(filename);
    if (itr != m_terrains.end())
    {
        return true;
    }

    return false;
}

bool FileManager::TextureExists(const std::string& filename)
{
    auto itr = m_textures.find(filename);
    if (itr != m_textures.end())
    {
        return true;
    }

    return false;
}

void FileManager::Refresh()
{
    m_prefabs.clear();
    m_scenes.clear();
    m_scripts.clear();
    m_terrains.clear();
    m_textures.clear();

    {
        std::vector<std::string> prefabFiles;
        FileSystem::GetFilesByExtension(FileSystem::GetRelativeDataPath(), ".pfb", prefabFiles, true);
        for (auto& f : prefabFiles)
        {
            std::string name = f.substr(f.find_last_of("/") + 1);
            m_prefabs.insert({ name, f });
        }
    }

    {
        std::vector<std::string> sceneFiles;
        FileSystem::GetFilesByExtension(FileSystem::GetRelativeDataPath(), ".scn", sceneFiles, true);
        for (auto& f : sceneFiles)
        {
            std::string name = f.substr(f.find_last_of("/") + 1);
            m_scenes.insert({ name, f });
        }
    }

    {
        std::vector<std::string> scriptFiles;
        FileSystem::GetFilesByExtension(FileSystem::GetRelativeDataPath(), ".lua", scriptFiles, true);
        for (auto& f : scriptFiles)
        {
            std::string name = f.substr(f.find_last_of("/") + 1);
            m_scripts.insert({ name, f });
        }
    }

    {
        std::vector<std::string> terrainFiles;
        FileSystem::GetFilesByExtension(FileSystem::GetRelativeDataPath(), ".trn", terrainFiles, true);
        for (auto& f : terrainFiles)
        {
            std::string name = f.substr(f.find_last_of("/") + 1);
            m_terrains.insert({ name, f });
        }
    }
    
    {
        std::vector<std::string> textureFiles;
        FileSystem::GetFilesByExtension(FileSystem::GetRelativeDataPath(), ".png", textureFiles, true);
        for (auto& f : textureFiles)
        {
            std::string name = f.substr(f.find_last_of("/") + 1);
            m_textures.insert({ name, f });
        }
    }
}

void FileManager::SetUp()
{
    Refresh();
}

void FileManager::TearDown()
{
}
} // namespace snack
