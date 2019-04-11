#pragma once

#include "Components/BaseComponent.hpp"

#include <glm/glm.hpp>

namespace snack
{
class DirectionalLightComponent final : public BaseComponent
{
public:

    DirectionalLightComponent(Transform* transform);

    ~DirectionalLightComponent();

    std::string GetComponentID() override;

    f32 GetIntensity() const;

#ifdef SPY_EDITOR
    void OnEditorGizmo() override;

    void OnEditorInspector() override;
#endif

    void SetIntensity(f32 intensity);

private:

    f32 m_intensity;
    glm::vec4 m_color;
};
} // namespace snack
