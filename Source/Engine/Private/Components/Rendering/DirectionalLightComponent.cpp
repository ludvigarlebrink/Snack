#include "Components\Rendering\DirectionalLightComponent.hpp"
#include "Manager.hpp"
#include "Transform.hpp"
#ifdef SPY_EDITOR
#include "SketchInclude.hpp"
#endif
#include "UtilsInclude.hpp"

#include <algorithm>

namespace snack
{
DirectionalLightComponent::DirectionalLightComponent(Transform* transform)
    : BaseComponent(transform)
    , m_intensity(0.0f)
{
    Manager::Render()->RegisterDirectionalLightComponent(this);
}

DirectionalLightComponent::~DirectionalLightComponent()
{
    Manager::Render()->DeregisterDirectionalLightComponent(this);
}

std::string DirectionalLightComponent::GetComponentID()
{
    return CLASS_NAME(DirectionalLightComponent);
}

f32 DirectionalLightComponent::GetIntensity() const
{
    return m_intensity;
}

void DirectionalLightComponent::Load(cereal::JSONInputArchive& archive)
{
    BaseComponent::Load(archive);
}

#ifdef SPY_EDITOR
void DirectionalLightComponent::OnEditorGizmo()
{
    glm::mat4 model = GetTransform()->GetWorldMatrix();
    model[0] = glm::vec4(glm::normalize(glm::vec3(model[0])), model[0][3]);
    model[1] = glm::vec4(glm::normalize(glm::vec3(model[1])), model[1][3]);
    model[2] = glm::vec4(glm::normalize(glm::vec3(model[2])), model[2][3]);
    glm::vec3 position = model[3];

    SketchGizmo::LineOverdrawn(position, position + glm::vec3(model[0]),
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::LineOverdrawn(position + glm::vec3(model[1]) * 0.25f, 
        position + glm::vec3(model[0]) + glm::vec3(model[1]) * 0.25f,
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::LineOverdrawn(position + glm::vec3(model[1]) * -0.25f, 
        position + glm::vec3(model[0]) + glm::vec3(model[1]) * -0.25f,
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::LineOverdrawn(position + glm::vec3(model[2]) * 0.25f,
        position + glm::vec3(model[0]) + glm::vec3(model[2]) * 0.25f,
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    SketchGizmo::LineOverdrawn(position + glm::vec3(model[2]) * -0.25f,
        position + glm::vec3(model[0]) + glm::vec3(model[2]) * -0.25f,
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
}

void DirectionalLightComponent::OnEditorInspector()
{
    Sketch::FloatField("Intensity", m_intensity);
}
#endif

void DirectionalLightComponent::Save(cereal::JSONOutputArchive& archive)
{
    BaseComponent::Save(archive);
}

void DirectionalLightComponent::SetIntensity(f32 intensity)
{
    m_intensity = std::clamp(intensity, 0.0f, 100.0f);
}
} // namespace snack
