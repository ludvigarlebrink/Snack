#include "Components\Rendering\SpotlightComponent.hpp"
#include "Manager.hpp"
#ifdef SPY_EDITOR
#include "SketchInclude.hpp"
#endif

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
    return typeid(SpotlightComponent).name();
}

f32 SpotlightComponent::GetIntensity() const
{
    return m_intensity;
}

#ifdef SPY_EDITOR
void SpotlightComponent::OnEditorInspector()
{
    Sketch::FloatField("Intensity", m_intensity);
}
#endif

void SpotlightComponent::SetIntensity(f32 intensity)
{
    m_intensity = intensity;
}
} // namespace snack
