#include "SketchEvent.hpp"
#include "imgui/imgui.h"

namespace spy
{
SketchEvent::KeyState SketchEvent::m_keys[KEY_COUNT];
Key SketchEvent::m_keysDown[KEY_COUNT];
Key SketchEvent::m_keysUp[KEY_COUNT];

int32 SketchEvent::m_keysDownCount = 0;
int32 SketchEvent::m_keysUpCount = 0;

bool SketchEvent::ButtonDown(Button button)
{
    switch (button)
    {
    case Button::LEFT:
        return ImGui::GetIO().MouseClicked[0];
    case Button::MIDDLE:
        return ImGui::GetIO().MouseClicked[2];
    case Button::RIGHT:
        return ImGui::GetIO().MouseClicked[1];
    default:
        break;
    }

    return false;
}

bool SketchEvent::ButtonRepeat(Button button)
{
    switch (button)
    {
    case Button::LEFT:
        return ImGui::GetIO().MouseDown[0];
    case Button::MIDDLE:
        return ImGui::GetIO().MouseDown[2];
    case Button::RIGHT:
        return ImGui::GetIO().MouseDown[1];
    default:
        break;
    }

    return false;
}

bool SketchEvent::ButtonUp(Button button)
{
    switch (button)
    {
    case Button::LEFT:
        return ImGui::GetIO().MouseClicked[0];
    case Button::MIDDLE:
        return ImGui::GetIO().MouseClicked[2];
    case Button::RIGHT:
        return ImGui::GetIO().MouseClicked[1];
    default:
        break;
    }

    return false;
}

glm::vec2 SketchEvent::GetPointerPosition()
{
    int32 x = 0;
    int32 y = 0;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(static_cast<f32>(x), static_cast<f32>(y));
}

glm::vec2 SketchEvent::GetPointerGlobalPosition()
{
    int32 x = 0;
    int32 y = 0;
    SDL_GetGlobalMouseState(&x, &y);
    return glm::vec2(static_cast<f32>(x), static_cast<f32>(y));
}

bool SketchEvent::IsPointerOverWindow()
{
    return ImGui::IsMouseHoveringWindow();
}

bool SketchEvent::KeyDown(Key key)
{
    if (m_keys[static_cast<int32>(key)] == KeyState::DOWN)
    {
        return true;
    }
    return false;
}

bool SketchEvent::KeyRepeat(Key key)
{
    if (m_keys[static_cast<int32>(key)] == KeyState::DOWN || m_keys[static_cast<int32>(key)] == KeyState::REPEAT)
    {
        return true;
    }
    return false;
}

bool SketchEvent::KeyUp(Key key)
{
    if (m_keys[static_cast<int32>(key)] == KeyState::UP)
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
    for (int32 i = 0; i < m_keysDownCount; ++i)
    {
        m_keys[static_cast<int32>(m_keysDown[i])] = KeyState::REPEAT;
    }
    m_keysDownCount = 0;

    for (int32 i = 0; i < m_keysUpCount; ++i)
    {
        m_keys[static_cast<int32>(m_keysUp[i])] = KeyState::NONE;
    }
    m_keysUpCount = 0;
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
            m_keys[static_cast<int32>(key)] = KeyState::DOWN;
            m_keysDown[m_keysDownCount] = key;
            ++m_keysDownCount;
        }
        break;
    }
    case SDL_KEYUP:
    {
        Key key = GetKey(event->key.keysym.sym);
        if (key != Key::UKNOWN)
        {
            m_keys[static_cast<int32>(key)] = KeyState::UP;
            m_keysUp[m_keysUpCount] = key;
            ++m_keysUpCount;
        }
        break;
    }
    default:
        break;
    }
}
} // namespace spy
