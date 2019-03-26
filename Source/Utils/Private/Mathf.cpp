#include "MathF.hpp"

namespace spy
{
const f32 PI = 3.14159265359f;

f32 Mathf::Clamp(f32 min, f32 max, f32 value)
{
    if (value > max)
    {
        return max;
    }

    if (value < min)
    {
        return min;
    }

    return value;
}

f32 Mathf::DegToRad(f32 deg)
{
    return deg * 0.0174532925f;
}

f32 Mathf::Lerp(f32 start, f32 end, f32 t)
{
    return start + t * (end - start);
}

f32 Mathf::Max(f32 a, f32 b)
{
    return a > b ? a : b;
}

f32 Mathf::Min(f32 a, f32 b)
{
    return a < b ? a : b;
}

f32 Mathf::RadToDeg(f32 rad)
{
    return rad * 57.2957795f;
}

uint32 Mathf::UpperPowerOfTwo(uint32 v)
{
    --v;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    ++v;
    return v;
}
} // namespace spy
