#pragma once

#include "BaseTypes.hpp"

#include <glm/glm.hpp>

namespace snack
{
class UTILS_API Intersection
{
public:

    struct RayHitData
    {
        f32 tMin;
        f32 tMax;
        glm::vec3 point;
        glm::vec3 normal;
    };

public:

    static bool RayVsOBB(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& aabbMin, const glm::vec3& aabbMax, const glm::mat4& modelMatrix, RayHitData& hit);
    
    static bool RayVsPlane(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& normal, const glm::vec3& point, RayHitData& hit);

    static bool RayVsSphere(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& center, f32 radius, RayHitData& hit);
};
} // namespace snack
