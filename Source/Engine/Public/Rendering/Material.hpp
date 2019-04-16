#pragma once

#include "RenderCoreForward.hpp"

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>
#include <string>

namespace snack
{
class ENGINE_API Material final
{
private:
    
    struct TextureProperty 
    {
        std::string filepath;
        Texture* texture;
        glm::vec4 color;
    };

public:
    
    Material();
    
    ~Material();

    glm::vec4 GetColor(const std::string& id);

    std::vector<std::string> GetIds();

    Shader* GetShader();

    Texture* GetTexture(const std::string& id);
    
    /**
     * @brief Load the material.
     * @param filepath File to load from
     * @ return False, is unsuccessful
     */
    bool Load(const std::string& filepath);
    
    Texture* LoadTexture(const std::string& filepath, const std::string& id);
    
    Texture* LoadTexture(const std::string& filepath, const std::string& id, const glm::vec4& color);

    /**
     * @brief Save the material.
     * @param filepath File to save to.
     * @return False, is unsuccessful.
     */
    bool Save(const std::string& filepath);

    void SetColor(const std::string& id, const glm::vec4& color);

    void SetShader(Shader* shader);

    void SetTexture(const std::string& id, Texture* texture);

    void SetTexture(const std::string& id, Texture* texture, const glm::vec4& color);

private:
    
    std::unordered_map<std::string, TextureProperty> m_textures;
    Shader* m_shader;
};
} // namespace snack
