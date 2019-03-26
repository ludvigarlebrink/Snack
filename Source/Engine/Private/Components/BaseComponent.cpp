#include "Components/BaseComponent.hpp"
#include "SketchInclude.hpp"
#include "Transform.hpp"

namespace spy
{
BaseComponent::BaseComponent(Transform* pEntity)
    : m_isEnabled(true)
    , m_pTransform(pEntity)
{
}

BaseComponent::~BaseComponent()
{
}

Transform* BaseComponent::GetTransform() const
{
    return m_pTransform;
}

bool BaseComponent::IsEnabled() const
{
    return m_isEnabled;
}

void BaseComponent::OnEditorGizmo()
{
    // Do nothing...
}

void BaseComponent::OnEditorInspector()
{
    Sketch::Checkbox("Enabled", m_isEnabled);
}

void BaseComponent::SetEnabled(bool enabled)
{
    m_isEnabled = enabled;
}
} // namespace spy
