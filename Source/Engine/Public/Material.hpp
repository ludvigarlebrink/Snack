#pragma once

#include "RenderCoreForward.hpp"

#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

namespace spy
{
class ENGINE_API Material final
{
private:
    
    struct TextureProperty 
    {
        std::string filename;
        Texture* texture;
        glm::vec4 color;
    };

public:
    
    Material();
    
    ~Material();

    glm::vec4 GetColor(const std::string& uniform);

    Texture* GetTexture(const std::string& uniform);
    
    bool Load(const std::string& filename);
    
    Texture* LoadTexture(const std::string& filename, const std::string& id);
    
    Texture* LoadTexture(const std::string& filename, const std::string& id, const glm::vec4& color);

    /**
     * @brief Save the material.
     * @param filename File to save to.
     * @return False, is unsuccessful.
     */
    bool Save(const std::string& filename);

    void SetColor(const std::string& id, const glm::vec4& color);

    void SetTexture(const std::string& id, Texture* texture);

    void SetTexture(const std::string& id, Texture* texture, const glm::vec4& color);

private:
    
    std::unordered_map<std::string, TextureProperty> m_textures;
};
} // namespace spy
