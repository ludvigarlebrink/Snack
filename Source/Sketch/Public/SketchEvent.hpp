#pragma once

#include "Input/Button.hpp"
#include "Input/Key.hpp"
#include "Input/Mod.hpp"

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <string>

namespace snack
{
class SketchInternal;

class SKETCH_API SketchEvent
{
    friend SketchInternal;

private:

    enum class State
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

    static bool DropFile();

    static std::string DropFilename();

    static glm::vec2 GetPointerDelta();

    static glm::vec2 GetPointerGlobalPosition();
    
    static glm::vec2 GetPointerPosition();

    static bool IsPointerOverWindow();

    static bool KeyDown(Key key);

    static bool KeyDown(Key key, Mod mod);

    static bool KeyRepeat(Key key);

    static bool KeyUp(Key key);

    static bool ModRepeat(Mod mod);

    static void ShowPointer(bool show);

    static bool WantsToClose();

    static void WrapPointerGlobal(const glm::vec2& position);

private:

    static Button GetButton(int32 button);
    
    static Key GetKey(int32 key);

    static void UpdateEvents();

    static void ProcessEvent(SDL_Event* event);

private:

    static const int32 KEY_COUNT = 512;
    static const int32 BUTTON_COUNT = 5;

    static State m_keys[KEY_COUNT];
    static Key m_keysDown[KEY_COUNT];
    static Key m_keysUp[KEY_COUNT];
    static int32 m_keyDownCount;
    static int32 m_keyUpCount;

    static State m_buttons[BUTTON_COUNT];
    static Button m_buttonsDown[KEY_COUNT];
    static Button m_buttonsUp[KEY_COUNT];
    static int32 m_buttonDownCount;
    static int32 m_buttonUpCount;

    static bool m_closeRequest;
    static bool m_dropFile;

    static std::string m_filename;
};
} // namespace snack
