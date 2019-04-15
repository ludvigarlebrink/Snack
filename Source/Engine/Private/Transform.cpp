#include "Transform.hpp"
#include "Components/BaseComponent.hpp"
#include "Manager.hpp"
#include "Log.hpp"
#ifdef SPY_EDITOR
#include "Sketch.hpp"
#endif

namespace snack
{
Transform::Transform(Transform* parent, InstanceID instanceID)
    : m_name("Transform")
    , m_instanceID(instanceID)
    , m_isEnabled(true)
    , m_isStaic(false)
    , m_isScene(false)
    , m_depth(0)
    , m_parent(parent)
    , m_position(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_rotation(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
    if (m_parent)
    {
        m_parent->m_children.push_back(this);

        // One higher depth than parent.
        m_depth = m_parent->m_depth + 1;
    }
}

Transform::~Transform()
{
    for (auto e : m_children)
    {
        delete e;
    }

    m_children.clear();

    for (auto c : m_components)
    {
        delete c.second;
    }

    m_components.clear();

    if (m_parent)
    {
        for (int32 i = 0; i < m_parent->m_children.size(); ++i)
        {
            if (m_parent->m_children[i] == this)
            {
                m_parent->m_children.erase(m_parent->m_children.begin() + i);
                break;
            }
        }
    }
}

BaseComponent* Transform::AddComponent(const std::string& id)
{
    auto itr = m_components.find(id);
    if (itr != m_components.end())
    {
        SPY_LOG_ERROR("Transform already has " << id << " component attached to it.");
        return nullptr;
    }

    BaseComponent* component = Manager::Class()->CreateComponent(id, this);
    m_components.insert({ id, component });
    return component;
}

void Transform::GetAllComponents(std::vector<BaseComponent*>& components)
{
    for (auto c : m_components)
    {
        components.push_back(c.second);
    }
}

Transform* Transform::GetChild(int32 index) const
{
    return m_children[index];
}

int32 Transform::GetChildCount() const
{
    return m_children.size();
}

BaseComponent* Transform::GetComponent(const std::string& id)
{
    auto c = m_components.find(id);
    if (c != m_components.end())
    {
        return c->second;
    }

    return nullptr;
}

int32 Transform::GetDepth() const
{
    return m_depth;
}

InstanceID Transform::GetInstanceID() const
{
    return m_instanceID;
}

glm::mat4 Transform::GetLocalMatrix() const
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    return glm::scale(model, m_scale);
}

glm::mat4 Transform::GetWorldMatrix() const
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, m_scale);

    if (m_parent)
    {
        return m_parent->GetWorldMatrix() * model;
    }

    return model;
}

std::string Transform::GetName() const
{
    return m_name;
}

Transform* Transform::GetParent() const
{
    return m_parent;
}

glm::vec3 Transform::GetLocalPosition() const
{
    return m_position;
}

glm::vec3 Transform::GetWorldPosition() const
{
    if (m_parent)
    {
        return m_parent->GetWorldMatrix() * glm::vec4(m_position, 1.0f);
    }

    return m_position;
}

glm::vec3 Transform::GetRotation() const
{
    return m_rotation;
}

glm::vec3 Transform::GetScale() const
{
    return m_scale;
}

bool Transform::HasComponent(const std::string & id)
{
    auto c = m_components.find(id);
    if (c != m_components.end())
    {
        return true;
    }

    return false;
}

bool Transform::IsEnabled() const
{
    return m_isEnabled;
}

bool Transform::IsLeaf() const
{
    return m_children.empty();
}

bool Transform::IsScene() const
{
    return m_isScene;
}

bool Transform::IsStatic() const
{
    return m_isStaic;
}

void Transform::Move(const glm::vec3& move)
{
    m_position += move;
}

void Transform::Move(f32 x, f32 y, f32 z)
{
    m_position += glm::vec3(x, y, z);
}

#ifdef SPY_EDITOR
void Transform::OnEditorInspector()
{
    Sketch::Checkbox("Enabled", m_isEnabled);
    Sketch::SameLine();
    Sketch::Checkbox("Static", m_isStaic);
    Sketch::TextField("Name", m_name);
    Sketch::Vec3Field("Position", m_position);
    Sketch::Vec3Field("Rotation", m_rotation);
    Sketch::Vec3Field("Scale", m_scale);
}
#endif

bool Transform::RemoveComponent(const std::string& id)
{
    auto itr = m_components.find(id);
    if (itr != m_components.end())
    {
        delete itr->second;
        m_components.erase(itr);
        return true;
    }

    return false;
}

void Transform::Scale(const glm::vec3& scale)
{
    m_scale += scale;
}

void Transform::Scale(f32 x, f32 y, f32 z)
{
    m_scale += glm::vec3(x, y, z);
}

void Transform::SetEnabled(bool enabled)
{
    m_isEnabled = enabled;
}

void Transform::SetName(const std::string& name)
{
    m_name = name;
}

void Transform::SetParent(Transform* parent)
{
    // Cannot reparent scene.
    if (m_isScene)
    {
        SPY_LOG("Cannot reparent scene: " + m_name);
        return;
    }

    if (m_parent)
    {
        for (int32 i = 0; i < m_parent->m_children.size(); ++i)
        {
            if (m_parent->m_children[i] == this)
            {
                m_parent->m_children.erase(m_parent->m_children.begin() + i);
                break;
            }
        }
    }

    m_parent = parent;
    if (m_parent == nullptr)
    {
        m_parent = Manager::Scene()->GetSceneRoot();
    }

    m_parent->m_children.push_back(this);

    // One higher depth than parent.
    m_depth = m_parent->m_depth + 1;
}

void Transform::SetLocalPosition(const glm::vec3& position)
{
    m_position = position;
}

void Transform::SetLocalPosition(f32 x, f32 y, f32 z)
{
    m_position = glm::vec3(x, y, z);
}

void Transform::SetRotation(const glm::vec3& rotation)
{
    m_rotation = rotation;
}

void Transform::SetRotation(f32 x, f32 y, f32 z)
{
    m_rotation = glm::vec3(x, y, z);
}

void Transform::SetScale(const glm::vec3& scale)
{
    m_scale = glm::max(scale, glm::vec3(F32_EPSILON));
}

void Transform::SetScale(f32 x, f32 y, f32 z)
{
    m_scale = glm::max(glm::vec3(x, y, z), glm::vec3(F32_EPSILON));
}

void Transform::SetScale(f32 uniform)
{
    m_scale = glm::max(glm::vec3(uniform), glm::vec3(F32_EPSILON));
}

void Transform::SetWorldPosition(const glm::vec3& position)
{
    m_position = position;
}

void Transform::SetWorldPosition(f32 x, f32 y, f32 z)
{
    m_position = glm::vec3(x, y, z);
}

void Transform::Load(cereal::JSONInputArchive& archive)
{
    if (m_isScene)
    {
        int32 count = 0;
        archive(count);
        for (int32 i = 0; i < count; ++i)
        {
            Transform* child = Manager::Scene()->Instantiate(this);
            child->Load(archive);
        }
    }
    else
    {
        archive.startNode();
        {
            archive(
                cereal::make_nvp("name", m_name),

                cereal::make_nvp("isEnabled", m_isEnabled),
                cereal::make_nvp("isStatic", m_isStaic),

                cereal::make_nvp("positionX", m_position.x),
                cereal::make_nvp("positionY", m_position.y),
                cereal::make_nvp("positionZ", m_position.z),

                cereal::make_nvp("rotationX", m_rotation.x),
                cereal::make_nvp("rotationY", m_rotation.y),
                cereal::make_nvp("rotationZ", m_rotation.z),

                cereal::make_nvp("scaleX", m_scale.x),
                cereal::make_nvp("scaleY", m_scale.y),
                cereal::make_nvp("scaleZ", m_scale.z)
            );

            archive.setNextName("children");
            archive.startNode();
            {
                int32 count = 0;
                archive(count);
                for (int32 i = 0; i < count; ++i)
                {
                    Transform* child = Manager::Scene()->Instantiate(this);
                    child->Load(archive);
                }
            }
            archive.finishNode();
        }
        archive.finishNode();
    }
}

void Transform::Save(cereal::JSONOutputArchive& archive)
{
    if (m_isScene)
    {
        archive(m_children.size());
        for (auto c : m_children)
        {
            c->Save(archive);
        }
    }
    else
    {
        archive.startNode();
        {
            archive(
                cereal::make_nvp("name", m_name),

                cereal::make_nvp("isEnabled", m_isEnabled),
                cereal::make_nvp("isStatic", m_isStaic),

                cereal::make_nvp("positionX", m_position.x),
                cereal::make_nvp("positionY", m_position.y),
                cereal::make_nvp("positionZ", m_position.z),

                cereal::make_nvp("rotationX", m_rotation.x),
                cereal::make_nvp("rotationY", m_rotation.y),
                cereal::make_nvp("rotationZ", m_rotation.z),

                cereal::make_nvp("scaleX", m_scale.x),
                cereal::make_nvp("scaleY", m_scale.y),
                cereal::make_nvp("scaleZ", m_scale.z)
            );

            archive.setNextName("children");
            archive.startNode();
            {
                archive.makeArray();
                archive(m_children.size());
                for (auto c : m_children)
                {
                    c->Save(archive);
                }
            }
            archive.finishNode();
        }
        archive.finishNode();
    }
}
} // namespace snack
