#pragma once

#include "Components/BaseComponent.hpp"
#include "Mesh.hpp"

#include <glm/glm.hpp>

namespace spy
{
/**
 * @brief A mesh component.
 */
class MeshComponent final : public BaseComponent
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
    };

public:

    MeshComponent(Transform* transform);

    ~MeshComponent();

    std::string GetComponentID() override;

    Mesh* GetMesh() const;

    f32 GetSphereRadius() const;

#ifdef SPY_EDITOR
    void OnEditorGizmo() override;

    void OnEditorInspector() override;
#endif

private:

    Mesh* m_mesh;
    f32 m_sphereRadius;
    glm::vec3 m_aabbMax;
    glm::vec3 m_aabbMin;
};
} // namespace spy

/**
 * @class spy::MeshComponent
 * @ingroup Engine
 */
