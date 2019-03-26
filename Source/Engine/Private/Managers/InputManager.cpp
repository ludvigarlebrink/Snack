#include "InputManager.hpp"
#ifdef SPY_EDITOR
#include "SketchInternal.hpp"
#endif

#include <SDL/SDL.h>

namespace spy
{
InputManager::InputManager()
    : m_keysDownCount(0)
    , m_keysUpCount(0)
{
    SetUp();
}

InputManager::~InputManager()
{
    TearDown();
}

bool InputManager::ButtonDown(Button button) const
{
    return false;
}

bool InputManager::ButtonRepeat(Button button) const
{
    return false;
}

bool InputManager::ButtonUp(Button button) const
{
    return false;
}

bool InputManager::KeyDown(Key key) const
{
    if (m_keys[static_cast<int32>(key)] == KeyState::DOWN)
    {
        return true;
    }
    return false;
}

bool InputManager::KeyRepeat(Key key) const
{
    if (m_keys[static_cast<int32>(key)] == KeyState::DOWN || m_keys[static_cast<int32>(key)] == KeyState::REPEAT)
    {
        return true;
    }
    return false;
}

bool InputManager::KeyUp(Key key) const
{
    if (m_keys[static_cast<int32>(key)] == KeyState::UP)
    {
        return true;
    }
    return false;
}

void InputManager::ProcessEvents()
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

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
    #ifdef SPY_EDITOR
        SketchInternal::ProcessEvent(&event);
    #endif
        switch (event.type)
        {
        case SDL_KEYDOWN:
        {
            Key key = GetKey(event.key.keysym.sym);
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
            Key key = GetKey(event.key.keysym.sym);
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
}

Key InputManager::GetKey(int32 key)
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

void InputManager::SetUp()
{
    for (int32 i = 0; i < KEY_COUNT; ++i)
    {
        m_keys[i] = KeyState::NONE;
    }
}

void InputManager::TearDown()
{
}
} // namespace spy
