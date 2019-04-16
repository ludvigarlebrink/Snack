#include "AssetManager.hpp"
#include "Components/Rendering/MeshComponent.hpp"
#include "FileSystem.hpp"
#include "Rendering/Terrain.hpp"
#include "Texture.hpp"

namespace snack
{
AssetManager::AssetManager()
{
    m_defaultMaterial = new Material();
    m_defaultMaterial->SetColor("Albedo", { 1.0, 1.0, 1.0, 1.0 });
}

AssetManager::~AssetManager()
{
}

void AssetManager::DestroyTerrain(const std::string& filepath)
{
    auto itr = m_terrains.find(filepath);
    if (itr != m_terrains.end())
    {
        itr->second.first--;
        if (itr->second.first <= 0)
        {
            delete itr->second.second;
            m_terrains.erase(filepath);
        }
    }
}

void AssetManager::DestroyTexture(const std::string& filepath)
{
    auto itr = m_textures.find(filepath);
    if (itr != m_textures.end())
    {
        itr->second.first--;
        if (itr->second.first <= 0)
        {
            delete itr->second.second;
            m_textures.erase(filepath);
        }
    }
}

Material* AssetManager::GetDefaultMaterial()
{
    return m_defaultMaterial;
}

Material * AssetManager::LoadMaterial(const std::string & filepath)
{
    auto itr = m_materials.find(filepath);
    if (itr != m_materials.end())
    {
        itr->second.first++;
        return itr->second.second;
    }

    Material* material = new Material();
    material->Load(FileSystem::GetRelativeDataPath(filepath));
    m_materials.insert({ filepath, { 1, material } });
    return material;
}

Terrain* AssetManager::LoadTerrain(const std::string& filepath)
{
    auto itr = m_terrains.find(filepath);
    if (itr != m_terrains.end())
    {
        itr->second.first++;
        return itr->second.second;
    }

    Terrain* terrain = new Terrain();
    terrain->Load(filepath);
    m_terrains.insert({ filepath, { 1, terrain } });
    return terrain;
}

Texture* AssetManager::LoadTexture(const std::string& filepath)
{
    auto itr = m_textures.find(filepath);
    if (itr != m_textures.end())
    {
        itr->second.first++;
        return itr->second.second;
    }

    Texture* pTexture = new Texture();
    pTexture->LoadFromFile(FileSystem::GetRelativeDataPath(filepath), Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE);
    m_textures.insert({ filepath, std::pair<int32, Texture*>(1, pTexture) });
    return pTexture;
}
} // namespace snack
