#pragma once

#include "RenderCoreForward.hpp"

#include <glm/glm.hpp>

namespace snack
{
class ENGINE_API Terrain final
{
public:

    Terrain();

    ~Terrain();

private:

    void SetUp();

    void TearDown();

private:

    glm::vec2 m_size;
};
} // namespace snack
