#include "AssetManager.hpp"
#include "Components/Rendering/MeshComponent.hpp"
#include "FileSystem.hpp"
#include "Texture.hpp"

namespace spy
{
AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::DestroyTexture(const std::string& filename)
{
    auto itr = m_textures.find(filename);
    if (itr != m_textures.end())
    {
        itr->second.first--;
        if (itr->second.first <= 0)
        {
            delete itr->second.second;
            m_textures.erase(filename);
        }
    }
}

Texture* AssetManager::LoadTexture(const std::string& filename)
{
    auto itr = m_textures.find(filename);
    if (itr != m_textures.end())
    {
        itr->second.first++;
        return itr->second.second;
    }

    Texture* pTexture = new Texture();
    pTexture->LoadFromFile(FileSystem::GetRelativeDataPath(filename), Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE);
    m_textures.insert({ filename, std::pair<int32, Texture*>(1, pTexture) });
    return pTexture;
}
} // namespace spy
