#pragma once

#include "Managers/IInputManager.hpp"

namespace spy
{
class InputManager final : public IInputManager
{
private:

    enum class KeyState
    {
        NONE,
        DOWN,
        REPEAT,
        UP,
    };

public:

    InputManager();

    ~InputManager();

    bool ButtonDown(Button button) const override;

    bool ButtonRepeat(Button button) const override;

    bool ButtonUp(Button button) const override;

    bool KeyDown(Key key) const override;

    bool KeyRepeat(Key key) const override;

    bool KeyUp(Key key) const override;

    void ProcessEvents() override;

private:

    Key GetKey(int32 key);

    void SetUp();

    void TearDown();

private:

    static const int32 KEY_COUNT = 512;

    KeyState m_keys[KEY_COUNT];
    Key m_keysDown[KEY_COUNT];
    Key m_keysUp[KEY_COUNT];

    int32 m_keysDownCount;
    int32 m_keysUpCount;
};
} // namespace spy
