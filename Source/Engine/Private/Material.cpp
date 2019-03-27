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
}
