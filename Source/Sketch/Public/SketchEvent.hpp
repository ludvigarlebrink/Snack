#pragma once

#include "Input/Button.hpp"
#include "Input/Key.hpp"
#include "Input/Mod.hpp"

#include <SDL/SDL.h>
#include <glm/glm.hpp>

namespace spy
{
class SketchInternal;

class SKETCH_API SketchEvent
{
    friend SketchInternal;

private:

    enum class KeyState
    {
        NONE,
        DOWN,
        REPEAT,
        UP,
    };

public:

    static bool ButtonDown(Button button);

    static bool ButtonRepeat(Button button);

    static bool ButtonUp(Button button);

    static glm::vec2 GetPointerPosition();

    static glm::vec2 GetPointerGlobalPosition();

    static bool IsPointerOverWindow();

    static bool KeyDown(Key key);

    static bool KeyRepeat(Key key);

    static bool KeyUp(Key key);

    static bool ModRepeat(Mod mod);


    static void ShowPointer(bool show);

    static void WrapPointerGlobal(const glm::vec2& position);

private:

    static Key GetKey(int32 key);

    static void UpdateEvents();

    static void ProcessEvent(SDL_Event* event);

private:

    static const int32 KEY_COUNT = 512;

    static KeyState m_keys[KEY_COUNT];
    static Key m_keysDown[KEY_COUNT];
    static Key m_keysUp[KEY_COUNT];
    static int32 m_keysDownCount;
    static int32 m_keysUpCount;
};
} // namespace spy
