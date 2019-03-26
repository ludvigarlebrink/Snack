#pragma once

#include "BaseTypes.hpp"

namespace spy
{
class UTILS_API Timer
{
public:

    Timer();

    ~Timer();

    f32 GetElapsedSeconds();

    void Reset();

private:

    uint64 m_start;
};
} // namespace spy
