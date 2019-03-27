#include "Material.hpp"
#include "Manager.hpp"

namespace spy 
{
Material::Material()
{
}

Material::~Material()
{
}

Texture* Material::LoadTexture(const std::string & filename, const std::string & uniform)
{
    return LoadTexture(filename, uniform, glm::vec4(1.0, 1.0, 1.0, 1.0));
}

Texture* Material::LoadTexture(const std::string& filename, const std::string& uniform, const glm::vec4& color)
{
    Texture* texture = Manager::Asset()->LoadTexture(filename);
    m_textures.insert({ uniform, {texture, color} });
    return texture;
}

void Material::SetColor(const std::string & uniform, const glm::vec4 & color)
{
    auto itr = m_textures.find(uniform);
    if (itr != m_textures.end())
    {
        itr->second.color = color;
        return;
    }

    m_textures.insert({ uniform, {nullptr, color} });
}

void Material::SetTexture(const std::string & uniform, Texture * file)
{
    SetTexture(uniform, file, glm::vec4(1.0, 1.0, 1.0, 1.0));
}

void Material::SetTexture(const std::string & uniform, Texture * file, const glm::vec4 & color)
{
    auto itr = m_textures.find(uniform);
    if (itr != m_textures.end())
    {
        itr->second.texture = file;
        itr->second.color = color;
        return;
    }

    m_textures.insert({ uniform, {file, color} });

}
} // namespace spy
