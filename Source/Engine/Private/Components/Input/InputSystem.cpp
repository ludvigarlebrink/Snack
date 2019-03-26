#include "InputSystem.hpp"
#include "Components/Input/InputComponent.hpp"

#include <SDL/SDL.h>

namespace spy
{
InputSystem::InputSystem()
{
    SetUp();
}

InputSystem::~InputSystem()
{
    TearDown();
}

void InputSystem::Tick()
{
}

void InputSystem::SetUp()
{
    InputComponent::m_inputSystem = this;
}

void InputSystem::TearDown()
{
    InputComponent::m_inputSystem = nullptr;
}
} // namespace spy
