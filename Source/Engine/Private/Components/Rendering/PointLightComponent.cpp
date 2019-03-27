#include "Components/Rendering/PointLightComponent.hpp"
#include"SketchInclude.hpp"
#include "Manager.hpp"

namespace spy
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
    return typeid(PointLightComponent).name();
}

f32 PointLightComponent::GetIntensity() const
{
    return m_intensity;
}

#ifdef SPY_EDITOR
void PointLightComponent::OnEditorInspector()
{
    BaseComponent::OnEditorInspector();
}
#endif

void PointLightComponent::SetIntensity(f32 intensity)
{
    m_intensity = intensity;
}
} // namespace spy
