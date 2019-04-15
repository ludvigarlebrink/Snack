#include "Components\Rendering\SpotlightComponent.hpp"
#include "Manager.hpp"
#ifdef SPY_EDITOR
#include "SketchInclude.hpp"
#endif
#include "UtilsInclude.hpp"

#include <algorithm>

namespace snack
{
SpotlightComponent::SpotlightComponent(Transform* transform)
    : BaseComponent(transform)
    , m_intensity(0.0f)
{
    Manager::Render()->RegisterSpotlightComponent(this);
}

SpotlightComponent::~SpotlightComponent()
{
    Manager::Render()->DeregisterSpotlightComponent(this);
}

std::string SpotlightComponent::GetComponentID()
{
    return CLASS_NAME(SpotlightComponent);
}

f32 SpotlightComponent::GetIntensity() const
{
    return m_intensity;
}

void SpotlightComponent::Load(cereal::JSONInputArchive& archive)
{
    BaseComponent::Load(archive);
}

#ifdef SPY_EDITOR
void SpotlightComponent::OnEditorInspector()
{
    Sketch::FloatField("Intensity", m_intensity);
}
#endif

void SpotlightComponent::Save(cereal::JSONOutputArchive& archive)
{
    BaseComponent::Save(archive);
}

void SpotlightComponent::SetIntensity(f32 intensity)
{
    m_intensity = std::clamp(intensity, 0.0f, 100.0f);
}
} // namespace snack
