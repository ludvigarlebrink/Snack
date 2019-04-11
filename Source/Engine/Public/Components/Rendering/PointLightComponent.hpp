#pragma once

#include "Components/BaseComponent.hpp"

#include <glm/glm.hpp>

namespace snack
{
class PointLightComponent final : public BaseComponent
{
public:

    PointLightComponent(Transform* transform);

    ~PointLightComponent();

    std::string GetComponentID() override;

    f32 GetIntensity() const;

    void OnEditorInspector() override;

    void SetIntensity(f32 intensity);

private:

    f32 m_intensity;
    f32 m_range;
    glm::vec4 m_color;
};
} // namespace snack
