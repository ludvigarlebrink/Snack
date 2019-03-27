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
    
    Texture* LoadTexture(const std::string& filename, const std::string& uniform);
    
    Texture* LoadTexture(const std::string& filename, const std::string& uniform, const glm::vec4& color);

    void SetColor(const std::string& uniform, const glm::vec4& color);

    void SetTexture(const std::string& uniform, Texture* file);

    void SetTexture(const std::string& uniform, Texture* file, const glm::vec4& color);

private:
    
    std::unordered_map<std::string, TextureProperty> m_textures;
};
} // namespace spy
