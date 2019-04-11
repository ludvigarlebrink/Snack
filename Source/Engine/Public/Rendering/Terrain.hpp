#pragma once

#include "BaseTypes.hpp"
#include "RenderCoreForward.hpp"

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace snack
{
class ENGINE_API Terrain final
{
public:

    struct Vertex
    {
        glm::vec2 position;
    };

public:

    /**
     * @brief Creates a terrain.
     */
    Terrain();

    /**
     * @brief Destroys a terrain.
     */
    ~Terrain();

    int32 GetSize() const;

    bool Load(const std::string& filename);

    void Refresh();

    void Render();

    bool Save(const std::string& filename);

    void SetSize(int32 size);

private:

    void SetUp();

    void TearDown();

private:

    int32 m_size;
    int32 m_heightMapResolution;

    Mesh* m_mesh;
    std::vector<uint8> m_heightMapPixels;
};
} // namespace snack
