#include "Timer.hpp"

#include <SDL/SDL.h>

namespace spy
{
Timer::Timer()
{
    m_start = SDL_GetPerformanceCounter();
}

Timer::~Timer()
{
}

f32 Timer::GetElapsedSeconds()
{
    uint64 now = SDL_GetPerformanceCounter();
    return static_cast<f32>(now - m_start) / static_cast<f32>(SDL_GetPerformanceFrequency());
}

void Timer::Reset()
{
    m_start = SDL_GetPerformanceCounter();
}
} // namespace spy
