#pragma once

#include "Components/BaseComponent.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace snack
{
class ENGINE_API CameraComponent final : public BaseComponent
{
public:

    enum class RenderMode
    {
        /**
         * @brief Render in deferred mode.
         */
        DEFERRED,

        /**
         * @brief Render in forward mode.
         */
        FORWARD,
    };

    enum class Projection
    {
        /**
         * @brief Orthographic projection.
         */
        ORTHOGRAPHIC,

        /**
         * @brief Perspective projection.
         */
        PERSPECTIVE
    };

public:

    CameraComponent(Transform* transform);

    ~CameraComponent();

    std::string GetComponentID() override;

    f32 GetFarPlane() const;

    f32 GetFieldOfView() const;

    f32 GetNearPlane() const;
    
    Projection GetProjection() const;

    glm::mat4 GetProjectionMatrix(f32 width, f32 height) const;

    RenderMode GetRenderMode() const;

    glm::mat4 GetViewMatrix() const;

#ifdef SPY_EDITOR
    void OnEditorGizmo() override;

    void OnEditorInspector() override;
#endif

    void SetFarPlane(f32 farPlane);

    void SetFieldOfView(f32 fieldOfView);

    void SetNearPlane(f32 nearPlane);

    void SetProjection(Projection projection);

    void SetRenderMode(RenderMode renderMode);

    void SetSize(f32 size);

private:

    Projection m_projection;
    RenderMode m_renderMode;

    glm::mat4 m_projectionMatrix;

    f32 m_fieldOfView;
    f32 m_nearPlane;
    f32 m_farPlane;
    f32 m_size;
};
} // namespace snack
