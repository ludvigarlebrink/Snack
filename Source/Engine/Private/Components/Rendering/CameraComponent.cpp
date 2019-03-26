#include "Components/Rendering/CameraComponent.hpp"
#include "Manager.hpp"
#include "SketchInclude.hpp"
#include "Transform.hpp"

namespace spy
{
CameraComponent::CameraComponent(Transform* transform)
    : BaseComponent(transform)
    , m_projection(Projection::PERSPECTIVE)
    , m_fieldOfView(45.0f)
    , m_farPlane(1000.0f)
    , m_nearPlane(0.1f)
    , m_size(20.0f)
{
    Manager::Render()->RegisterCameraComponent(this);
}

CameraComponent::~CameraComponent()
{
    Manager::Render()->DeregisterCameraComponent(this);
}

std::string CameraComponent::GetComponentID()
{
    return typeid(CameraComponent).name();
}

f32 CameraComponent::GetFarPlane() const
{
    return m_farPlane;
}

f32 CameraComponent::GetFieldOfView() const
{
    return m_fieldOfView;
}

f32 CameraComponent::GetNearPlane() const
{
    return m_nearPlane;
}

CameraComponent::Projection CameraComponent::GetProjection() const
{
    return m_projection;
}

glm::mat4 CameraComponent::GetProjectionMatrix(f32 width, f32 height) const
{
    switch (m_projection)
    {
    case Projection::ORTHOGRAPHIC:
    {
        f32 aspect = width / height;
        return glm::ortho(m_size * aspect * -0.5f, m_size * aspect * 0.5f, m_size * -0.5f, m_size * 0.5f, m_nearPlane, m_farPlane);
    }
    case Projection::PERSPECTIVE:
    {
        return glm::perspective(m_fieldOfView, width / height, m_nearPlane, m_farPlane);
    }
    default:
        break;
    }

    return glm::mat4(1.0);
}

glm::mat4 CameraComponent::GetViewMatrix() const
{
    return glm::inverse(GetTransform()->GetWorldMatrix());
}

void CameraComponent::OnEditorInspector()
{
#ifdef SPY_EDITOR
    BaseComponent::OnEditorInspector();

    Sketch::FloatField("Near Plane", m_nearPlane);
    Sketch::FloatField("Far Plane", m_farPlane);
    
    std::string selectedProjection;
    if (m_projection == Projection::ORTHOGRAPHIC)
    {
        selectedProjection = "Orthographic";
    }
    else
    {
        selectedProjection = "Perspective";
    }

    if (SketchCombo::Begin("Projection Combo", selectedProjection))
    {
        if (SketchCombo::Selectable("Orthographic"))
        {
            m_projection = Projection::ORTHOGRAPHIC;
        }
    
        if (SketchCombo::Selectable("Perspective"))
        {
            m_projection = Projection::PERSPECTIVE;
        }
    
        SketchCombo::End();
    }

    if (m_projection == Projection::ORTHOGRAPHIC)
    {
        Sketch::FloatField("Size", m_size);
    }
    else
    {
        Sketch::FloatField("Field of View", m_size);
    }
#endif
}

void CameraComponent::SetFarPlane(f32 farPlane)
{
    m_farPlane = farPlane;
}

void CameraComponent::SetFieldOfView(f32 fieldOfView)
{
    m_fieldOfView = fieldOfView;
}

void CameraComponent::SetNearPlane(f32 nearPlane)
{
    m_nearPlane = nearPlane;
}

void CameraComponent::SetProjection(Projection projection)
{
    m_projection = projection;
}

void CameraComponent::SetSize(f32 size)
{
    m_size = size;
}
} // namespace spy
