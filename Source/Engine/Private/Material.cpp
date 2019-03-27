#include "Material.hpp"
#include "Manager.hpp"

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <fstream>
#include <sstream>

namespace spy
{
Material::Material()
{
}

Material::~Material()
{
}

glm::vec4 Material::GetColor(const std::string & id)
{
    auto itr = m_textures.find(id);
    if (itr != m_textures.end())
    {
        return itr->second.color;
    }
    return glm::vec4(1.0, 1.0, 1.0, 1.0);
}

std::vector<std::string> Material::GetIds()
{
    std::vector<std::string> ids = std::vector<std::string>();
    for (auto itr = m_textures.begin(); itr != m_textures.end(); ++itr) 
    {
        ids.push_back(itr->first);
    }
    return ids;
}

Texture * Material::GetTexture(const std::string & id)
{
    auto itr = m_textures.find(id);
    if (itr != m_textures.end())
    {
        return itr->second.texture;
    }
    return nullptr;
}

bool Material::Load(const std::string& filename)
{
    std::ifstream f(filename);
    if (!f.is_open())
    {
        f.close();
        return false;
    }

    std::stringstream ss;
    ss << f.rdbuf();
    {
        cereal::JSONOutputArchive ar(ss);
    }

    return true;
}

Texture* Material::LoadTexture(const std::string& filename, const std::string& id)
{
    return LoadTexture(filename, id, glm::vec4(1.0, 1.0, 1.0, 1.0));
}

Texture* Material::LoadTexture(const std::string& filename, const std::string& id, const glm::vec4& color)
{
    Texture* texture = Manager::Asset()->LoadTexture(filename);
    m_textures.insert({ id, { filename, texture, color } });
    return texture;
}

bool Material::Save(const std::string& filename)
{
    std::stringstream ss;
    {
        cereal::JSONOutputArchive ar(ss);
        for (auto t : m_textures)
        {
            ar(cereal::make_nvp("id", t.first));
            if (t.second.texture)
            {
                ar(cereal::make_nvp("texture", t.second.filename));
            }
            ar(cereal::make_nvp("rColor", t.second.color.r));
            ar(cereal::make_nvp("gColor", t.second.color.g));
            ar(cereal::make_nvp("bColor", t.second.color.b));
            ar(cereal::make_nvp("aColor", t.second.color.a));
        }
    }

    std::ofstream f(filename);
    if (!f.is_open())
    {
        f.close();
        return false;
    }
    f << ss.str();
    f.close();

    return true;
}

void Material::SetColor(const std::string& id, const glm::vec4& color)
{
    auto itr = m_textures.find(id);
    if (itr != m_textures.end())
    {
        itr->second.color = color;
        return;
    }

    m_textures.insert({ id, { "", nullptr, color } });
}

void Material::SetTexture(const std::string& id, Texture* texture)
{
    SetTexture(id, texture, glm::vec4(1.0, 1.0, 1.0, 1.0));
}

void Material::SetTexture(const std::string& id, Texture* texture, const glm::vec4& color)
{
    auto itr = m_textures.find(id);
    if (itr != m_textures.end())
    {
        itr->second.texture = texture;
        itr->second.color = color;
        return;
    }

    m_textures.insert({ id, { "", texture, color } });
}
} // namespace spy
