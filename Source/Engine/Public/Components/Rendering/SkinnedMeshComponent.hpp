#pragma once

#include "Components/BaseComponent.hpp"

#include <glm/glm.hpp>

namespace spy
{
class SkinnedMeshComponent final : public BaseComponent
{
public:

    struct Vertex
    {
        /**
         * @brief Position of the vertex.
         */
        glm::vec3 position;

        /**
         * @brief Normal of the vertex.
         */
        glm::vec3 normal;

        /**
         * @brief Tangent of the vertex.
         */
        glm::vec3 tangent;

        /**
         * @brief Texture coordiantes of the vertex.
         */
        glm::vec2 textureCoordinates;

        glm::ivec4 jointID;

        glm::vec4 weights;
    };

public:

    SkinnedMeshComponent(Transform* transform);

    ~SkinnedMeshComponent();

    std::string GetComponentID() override;

    void OnEditorInspector() override;
};
} // namespace spy
