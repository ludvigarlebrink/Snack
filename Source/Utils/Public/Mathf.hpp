#pragma once

#include "BaseTypes.hpp"

namespace spy
{
/**
 * @brief A collection of mathematical functions.
 */
class UTILS_API Mathf
{
public:

    /**
     * @brief Clamps a value between a minimum and a maximum float.
     *
     * @param min Minimum value.
     * @param max Maximum value.
     * @param value Float to be clamped.
     * @return Clamped float.
     */
    static f32 Clamp(f32 min, f32 max, f32 value);

    /**
     * @brief Converts degrees to radians.
     *
     * @param deg Degrees as be converted.
     * @return Radians.
     */
    static f32 DegToRad(f32 deg);

    /**
     * @param Linear interpolation between two floats.
     *
     * @param start Start value.
     * @param end End value.
     * @param t Interpolation value.
     * @return A linear interpolated value.
     */
    static f32 Lerp(f32 start, f32 end, f32 t);

    /**
     * @brief Get the maximum of two floats.
     *
     * @param a First floats.
     * @param b Second floats.
     */
    static f32 Max(f32 a, f32 b);

    /**
     * @brief Get the minimum of two floats.
     *
     * @param a First floats.
     * @param b Second floats.
     */
    static f32 Min(f32 a, f32 b);

    /**
     * @brief Converts radians to degrees.
     *
     * @param rad Radians as be converted.
     * @return Degrees.
     */
    static f32 RadToDeg(f32 rad);

    static uint32 UpperPowerOfTwo(uint32 v);

public:

    /**
     * @brief A mathematical constant, shorthand for 3.14159265359.
     */
    static const f32 PI;
};
} // namespace spy

/**
 * @class spy::Mathf
 * @ingroup Math
 */
