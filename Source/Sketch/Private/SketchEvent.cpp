#include "SketchEvent.hpp"
#include "imgui/imgui.h"

namespace spy
{
SketchEvent::State SketchEvent::m_keys[KEY_COUNT];
Key SketchEvent::m_keysDown[KEY_COUNT];
Key SketchEvent::m_keysUp[KEY_COUNT];
int32 SketchEvent::m_keyDownCount = 0;
int32 SketchEvent::m_keyUpCount = 0;

SketchEvent::State SketchEvent::m_buttons[BUTTON_COUNT];
Button SketchEvent::m_buttonsDown[KEY_COUNT];
Button SketchEvent::m_buttonsUp[KEY_COUNT];
int32 SketchEvent::m_buttonDownCount = 0;
int32 SketchEvent::m_buttonUpCount = 0;

bool SketchEvent::m_closeRequest = false;
bool SketchEvent::m_dropFile = false;

std::string SketchEvent::m_filename = "";

bool SketchEvent::ButtonDown(Button button)
{
    if (m_buttons[static_cast<int32>(button)] == State::DOWN)
    {
        return true;
    }
    return false;
}

bool SketchEvent::ButtonRepeat(Button button)
{
    if (m_buttons[static_cast<int32>(button)] == State::DOWN || m_buttons[static_cast<int32>(button)] == State::REPEAT)
    {
        return true;
    }
    return false;
}

bool SketchEvent::ButtonUp(Button button)
{
    if (m_buttons[static_cast<int32>(button)] == State::UP)
    {
        return true;
    }
    return false;
}

bool SketchEvent::CloseRequest()
{
    return m_closeRequest;
}

bool SketchEvent::DropFile()
{
    return m_dropFile;
}

std::string SketchEvent::DropFilename()
{
    return m_filename;
}

glm::vec2 SketchEvent::GetPointerDelta()
{
    return glm::vec2(ImGui::GetIO().MouseDelta.x, ImGui::GetIO().MouseDelta.y);
}

glm::vec2 SketchEvent::GetPointerGlobalPosition()
{
    int32 x = 0;
    int32 y = 0;
    SDL_GetGlobalMouseState(&x, &y);
    return glm::vec2(static_cast<f32>(x), static_cast<f32>(y));
}

glm::vec2 SketchEvent::GetPointerPosition()
{
    int32 x = 0;
    int32 y = 0;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(static_cast<f32>(x), static_cast<f32>(y));
}

bool SketchEvent::IsPointerOverWindow()
{
    return ImGui::IsMouseHoveringWindow();
}

bool SketchEvent::KeyDown(Key key)
{
    if (m_keys[static_cast<int32>(key)] == State::DOWN)
    {
        return true;
    }
    return false;
}

bool SketchEvent::KeyRepeat(Key key)
{
    if (m_keys[static_cast<int32>(key)] == State::DOWN || m_keys[static_cast<int32>(key)] == State::REPEAT)
    {
        return true;
    }
    return false;
}

bool SketchEvent::KeyUp(Key key)
{
    if (m_keys[static_cast<int32>(key)] == State::UP)
    {
        return true;
    }
    return false;
}

bool SketchEvent::ModRepeat(Mod mod)
{
    switch (mod)
    {
    case Mod::ALT:
        return ImGui::GetIO().KeyAlt;
    case Mod::CTRL:
        return ImGui::GetIO().KeyCtrl;
    case Mod::SHIFT:
        return ImGui::GetIO().KeyShift;
    default:
        break;
    }

    return false;
}

void SketchEvent::ShowPointer(bool show)
{
    SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
}

void SketchEvent::WrapPointerGlobal(const glm::vec2& position)
{
    SDL_WarpMouseGlobal(static_cast<f32>(position.x), static_cast<f32>(position.y));
}

Button SketchEvent::GetButton(int32 button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        return Button::LEFT;
    case SDL_BUTTON_MIDDLE:
        return Button::MIDDLE;
    case SDL_BUTTON_RIGHT:
        return Button::RIGHT;
    default:
        break;
    }

    return Button::UNKNOWN;
}

Key SketchEvent::GetKey(int32 key)
{
    switch (key)
    {
    case SDLK_SPACE:
    {
        return Key::SPACE;
    }
    case SDLK_a:
    {
        return Key::A;
    }
    case SDLK_b:
    {
        return Key::B;
    }
    case SDLK_c:
    {
        return Key::C;
    }
    case SDLK_d:
    {
        return Key::D;
    }
    case SDLK_e:
    {
        return Key::E;
    }
    case SDLK_f:
    {
        return Key::F;
    }
    case SDLK_g:
    {
        return Key::G;
    }
    case SDLK_h:
    {
        return Key::H;
    }
    case SDLK_i:
    {
        return Key::I;
    }
    case SDLK_j:
    {
        return Key::J;
    }
    case SDLK_k:
    {
        return Key::K;
    }
    case SDLK_l:
    {
        return Key::L;
    }
    case SDLK_m:
    {
        return Key::M;
    }
    case SDLK_n:
    {
        return Key::N;
    }
    case SDLK_o:
    {
        return Key::O;
    }
    case SDLK_p:
    {
        return Key::R;
    }
    case SDLK_q:
    {
        return Key::Q;
    }
    case SDLK_r:
    {
        return Key::R;
    }
    case SDLK_s:
    {
        return Key::S;
    }
    case SDLK_t:
    {
        return Key::T;
    }
    case SDLK_u:
    {
        return Key::U;
    }
    case SDLK_v:
    {
        return Key::V;
    }
    case SDLK_w:
    {
        return Key::W;
    }
    case SDLK_x:
    {
        return Key::X;
    }
    case SDLK_y:
    {
        return Key::Y;
    }
    case SDLK_z:
    {
        return Key::Z;
    }
    default:
        break;
    }

    return Key::UKNOWN;
}

void SketchEvent::UpdateEvents()
{
    for (int32 i = 0; i < m_keyDownCount; ++i)
    {
        m_keys[static_cast<int32>(m_keysDown[i])] = State::REPEAT;
    }
    m_keyDownCount = 0;

    for (int32 i = 0; i < m_keyUpCount; ++i)
    {
        m_keys[static_cast<int32>(m_keysUp[i])] = State::NONE;
    }
    m_keyUpCount = 0;

    for (int32 i = 0; i < m_buttonDownCount; ++i)
    {
        m_buttons[static_cast<int32>(m_buttonsDown[i])] = State::REPEAT;
    }
    m_buttonDownCount = 0;

    for (int32 i = 0; i < m_buttonUpCount; ++i)
    {
        m_buttons[static_cast<int32>(m_buttonsUp[i])] = State::NONE;
    }
    m_buttonUpCount = 0;

    m_closeRequest = false;
    m_dropFile = false;
    m_filename = "";
}

void SketchEvent::ProcessEvent(SDL_Event* event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
    {
        Key key = GetKey(event->key.keysym.sym);
        if (key != Key::UKNOWN)
        {
            m_keys[static_cast<int32>(key)] = State::DOWN;
            m_keysDown[m_keyDownCount] = key;
            ++m_keyDownCount;
        }
        break;
    }
    case SDL_KEYUP:
    {
        Key key = GetKey(event->key.keysym.sym);
        if (key != Key::UKNOWN)
        {
            m_keys[static_cast<int32>(key)] = State::UP;
            m_keysUp[m_keyUpCount] = key;
            ++m_keyUpCount;
        }
        break;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
        Button button = GetButton(event->button.button);
        if (button != Button::UNKNOWN)
        {
            m_buttons[static_cast<int32>(button)] = State::DOWN;
            m_buttonsDown[m_buttonDownCount] = button;
            ++m_buttonDownCount;
        }
        break;
    }
    case SDL_MOUSEBUTTONUP:
    {
        Button button = GetButton(event->button.button);
        if (button != Button::UNKNOWN)
        {
            m_buttons[static_cast<int32>(button)] = State::UP;
            m_buttonsUp[m_buttonUpCount] = button;
            ++m_buttonUpCount;
        }
        break;
    }
    case SDL_QUIT:
    {
        m_closeRequest = true;
        break;
    }
    case SDL_DROPFILE:
    {
        m_filename = event->drop.file;
        m_dropFile = true;
        break;
    }
    default:
        break;
    }
}
} // namespace spy
