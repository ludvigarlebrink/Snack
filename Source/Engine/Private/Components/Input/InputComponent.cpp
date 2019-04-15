#include "Components/Input/InputComponent.hpp"
#include "SketchInclude.hpp"
#include "UtilsInclude.hpp"

namespace snack
{
InputSystem* InputComponent::m_inputSystem = nullptr;

InputComponent::InputComponent(Transform* pTransform)
    : BaseComponent(pTransform)
{
}

InputComponent::~InputComponent()
{
}

bool InputComponent::ActionDown(const std::string& id)
{
    auto itr = m_actions.find(id);
    if (itr != m_actions.end())
    {
    }

    return false;
}

bool InputComponent::ActionRepeat(const std::string& id)
{
    auto itr = m_actions.find(id);
    if (itr != m_actions.end())
    {
    }

    return false;
}

bool InputComponent::ActionUp(const std::string& id)
{
    auto itr = m_actions.find(id);
    if (itr != m_actions.end())
    {
    }

    return false;
}

void InputComponent::DeregisterAction(const std::string& id)
{
    m_actions.erase(id);
}

std::string InputComponent::GetComponentID()
{
    return CLASS_NAME(InputComponent);
}

void InputComponent::OnEditorInspector()
{
    BaseComponent::OnEditorInspector();
    if (Sketch::Button("Add Action"))
    {
    }

    Sketch::SameLine();

    if (Sketch::Button("Add Axis"))
    {

    }
}

void InputComponent::RegisterAction(const std::string& id, Key key, Key altKey)
{
    Action action;
    action.key = key;
    action.altKey = altKey;
    
    m_actions.insert({ id, action });
}
} // namespace snack
