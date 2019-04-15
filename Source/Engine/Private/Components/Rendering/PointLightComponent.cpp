#include "Components/Rendering/PointLightComponent.hpp"
#include"SketchInclude.hpp"
#include "Manager.hpp"
#ifdef SPY_EDITOR
#include "SketchInclude.hpp"
#endif
#include "UtilsInclude.hpp"

#include <algorithm>

namespace snack
{
PointLightComponent::PointLightComponent(Transform* transform)
    : BaseComponent(transform)
    , m_intensity(1.0f)
    , m_range(10.0f)
    , m_color(1.0f, 1.0f, 0.9f, 1.0f)
{
    Manager::Render()->RegisterPointLightComponent(this);
}

PointLightComponent::~PointLightComponent()
{
    Manager::Render()->DeregisterPointLightComponent(this);
}

std::string PointLightComponent::GetComponentID()
{
    return CLASS_NAME(PointLightComponent);
}

f32 PointLightComponent::GetIntensity() const
{
    return m_intensity;
}

void PointLightComponent::Load(cereal::JSONInputArchive& archive)
{
    BaseComponent::Load(archive);
}

#ifdef SPY_EDITOR
void PointLightComponent::OnEditorInspector()
{
    BaseComponent::OnEditorInspector();
    Sketch::FloatField("Intensity", m_intensity);
}
#endif

void PointLightComponent::Save(cereal::JSONOutputArchive& archive)
{
    BaseComponent::Save(archive);
}

void PointLightComponent::SetIntensity(f32 intensity)
{
    m_intensity = std::clamp(intensity, 0.0f, 100.0f);
}
} // namespace snack
