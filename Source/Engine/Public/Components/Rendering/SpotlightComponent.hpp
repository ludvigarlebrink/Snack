#pragma once

#include "Components/BaseComponent.hpp"

#include <glm/glm.hpp>

namespace spy
{
class SpotlightComponent final : public BaseComponent
{
public:

    SpotlightComponent(Transform* transform);

    ~SpotlightComponent();

    std::string GetComponentID() override;

    f32 GetIntensity() const;

    void OnEditorInspector() override;

    void SetIntensity(f32 intensity);

private:

    f32 m_intensity;
    glm::vec4 m_color;
};
} // namespace spy
