#include "Rendering/Material.hpp"
#include "Manager.hpp"

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <fstream>
#include <sstream>
#include <cstring>

namespace snack
{
Material::Material()
{
}

Material::~Material()
{
}

glm::vec4 Material::GetColor(const std::string& id)
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

Shader* Material::GetShader()
{
    return m_shader;
}

Texture* Material::GetTexture(const std::string& id)
{
    auto itr = m_textures.find(id);
    if (itr != m_textures.end())
    {
        return itr->second.texture;
    }
    return nullptr;
}

bool Material::Load(const std::string& filepath)
{
    std::ifstream f(filepath);
    if (!f.is_open())
    {
        f.close();
        return false;
    }

    std::stringstream ss;
    ss << f.rdbuf();
    {
        cereal::JSONInputArchive ar(ss);

        int32 size = 0;
        while (const char* name = ar.getNodeName()) {
            ar.startNode();
            if (std::strcmp(name, "textures_size") == 0) {
                ar(cereal::make_nvp("size", size));
            }
            else if (std::strcmp(name, "textures") == 0)
            {
                for (int i = 0; i < size; ++i) 
                {
                    ar.startNode();
                    std::string id;
                    ar(cereal::make_nvp("id", id));

                    std::string texturename;
                    name = ar.getNodeName();
                    if (std::strcmp(name, "texture") == 0) {
                        ar(cereal::make_nvp("texture", texturename));
                    }

                    glm::vec4 color;
                    ar(cereal::make_nvp("rColor", color.r));
                    ar(cereal::make_nvp("gColor", color.g));
                    ar(cereal::make_nvp("bColor", color.b));
                    ar(cereal::make_nvp("aColor", color.a));
                    LoadTexture(texturename, id, color);
                    ar.finishNode();
                }
            }
            ar.finishNode();
        }
    }
    return true;
}

Texture* Material::LoadTexture(const std::string& filepath, const std::string& id)
{
    return LoadTexture(filepath, id, glm::vec4(1.0, 1.0, 1.0, 1.0));
}

Texture* Material::LoadTexture(const std::string& filepath, const std::string& id, const glm::vec4& color)
{
    Texture* texture = Manager::Asset()->LoadTexture(filepath);
    m_textures.insert({ id, { filepath, texture, color } });
    return texture;
}

bool Material::Save(const std::string& filepath)
{
    std::stringstream ss;
    {
        cereal::JSONOutputArchive ar(ss);
        ar.setNextName("info");
        ar.startNode();
        {
            ar(cereal::make_nvp("type", std::string("material")));
        }

        ar.finishNode();
        if (!m_textures.empty())
        {
            ar.setNextName("textures_size");
            ar.startNode();
            {
                ar(cereal::make_nvp("size", m_textures.size()));
            }
            ar.finishNode();
            ar.setNextName("textures");
            ar.startNode();
            ar.makeArray();
            for (auto t : m_textures)
            {
                ar.startNode();
                {
                    ar(cereal::make_nvp("id", t.first));
                    if (t.second.texture)
                    {
                        ar(cereal::make_nvp("texture", t.second.filepath));
                    }
                    ar(cereal::make_nvp("rColor", t.second.color.r));
                    ar(cereal::make_nvp("gColor", t.second.color.g));
                    ar(cereal::make_nvp("bColor", t.second.color.b));
                    ar(cereal::make_nvp("aColor", t.second.color.a));
                }
                ar.finishNode();
            }
            ar.finishNode();
        }
    }

    std::ofstream f(filepath);
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

void Material::SetShader(Shader* shader)
{
    m_shader = shader;
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
} // namespace snack
