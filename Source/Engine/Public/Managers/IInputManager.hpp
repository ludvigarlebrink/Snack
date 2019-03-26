#pragma once

#include "BaseTypes.hpp"
#include "Input/Button.hpp"
#include "Input/Key.hpp"

namespace spy
{
class ENGINE_API IInputManager
{
public:

    virtual ~IInputManager() = default;

    virtual bool ButtonDown(Button button) const = 0;

    virtual bool ButtonRepeat(Button button) const = 0;

    virtual bool ButtonUp(Button button) const = 0;

    virtual bool KeyDown(Key key) const = 0;

    virtual bool KeyRepeat(Key key) const = 0;

    virtual bool KeyUp(Key key) const = 0;

    virtual void ProcessEvents() = 0;
};
} // namespace spy
