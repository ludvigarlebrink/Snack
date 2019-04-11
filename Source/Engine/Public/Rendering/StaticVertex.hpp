#pragma once

#include <glm/glm.hpp>

namespace snack
{
/**
 * @brief A normal static vertex.
 */
struct StaticVertex
{
    /**
     * @brief The position of the vertex.
     */
    glm::vec3 position;

    /**
     * @brief The normal of the vertex.
     */
    glm::vec3 normal;

    /**
     * @brief The tangent of the vertex.
     */
    glm::vec3 tangent;

    /**
     * @brief The texture coodiante of the vertex.
     */
    glm::vec2 textureCoordinate;
};
} // namespace snack
