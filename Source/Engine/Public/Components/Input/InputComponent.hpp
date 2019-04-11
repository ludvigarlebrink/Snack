#pragma once

#include "Components/BaseComponent.hpp"
#include "Input/Button.hpp"
#include "Input/Key.hpp"

#include <string>
#include <unordered_map>

namespace snack
{
class InputSystem;

class ENGINE_API InputComponent final : public BaseComponent
{
    friend InputSystem;

private:

    struct Action
    {
        Key key;
        Key altKey;
    };

public:

    InputComponent(Transform* pTransform);

    ~InputComponent();
    
    bool ActionDown(const std::string& id);

    bool ActionRepeat(const std::string& id);

    bool ActionUp(const std::string& id);

    void DeregisterAction(const std::string& id);

    std::string GetComponentID() override;

    void OnEditorInspector() override;

    void RegisterAction(const std::string& id, Key key, Key altKey);

private:

    static InputSystem* m_inputSystem;

    std::unordered_map<std::string, Action> m_actions;
};
}
