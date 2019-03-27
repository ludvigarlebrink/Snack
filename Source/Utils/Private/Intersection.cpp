#include "Intersection.hpp"

#include <numeric>

namespace spy
{
bool Intersection::RayVsOBB(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& aabbMin, const glm::vec3& aabbMax, const glm::mat4& modelMatrix, RayHitData& hit)
{
    f32 tMin = 0.0f;
    f32 tMax = std::numeric_limits<f32>::max();

    glm::vec3 obbPositionWorld = glm::vec3(modelMatrix[3]);
    glm::vec3 delta = obbPositionWorld - origin;

    // X axis.
    {
        glm::vec3 xAxis(modelMatrix[0]);
        f32 e = glm::dot(xAxis, delta);
        f32 f = glm::dot(direction, xAxis);

        if (glm::abs(f) > 0.001f)
        {
            f32 t1 = (e + aabbMin.x) / f;
            f32 t2 = (e + aabbMax.x) / f;
            if (t1 > t2)
            {
                // Swap.
                f32 w = t1;
                t1 = t2;
                t2 = w;
            }
            if (t2 < tMax)
            {
                tMax = t2;
            }
            if (t1 > tMin)
            {
                tMin = t1;
            }
            if (tMax < tMin)
            {
                return false;
            }
        }
        else
        {
            if (aabbMin.x - e > 0.0f || aabbMax.x - e < 0.0f)
            {
                return false;
            }
        }
    }

    // Y axis.
    {
        glm::vec3 yAxis(modelMatrix[1]);
        f32 e = glm::dot(yAxis, delta);
        f32 f = glm::dot(direction, yAxis);

        if (glm::abs(f) > 0.001f)
        { 
            f32 t1 = (e + aabbMin.y) / f;
            f32 t2 = (e + aabbMax.y) / f;
            if (t1 > t2)
            {
                // Swap.
                f32 w = t1;
                t1 = t2;
                t2 = w;
            }
            if (t2 < tMax)
            {
                tMax = t2;
            }
            if (t1 > tMin)
            {
                tMin = t1;
            }
            if (tMax < tMin)
            {
                return false;
            }
        }
        else
        {
            if (aabbMin.y - e > 0.0f || aabbMax.y - e < 0.0f)
            {
                return false;
            }
        }
    }

    // Z axis.
    {
        glm::vec3 zAxis(modelMatrix[2]);
        f32 e = glm::dot(zAxis, delta);
        f32 f = glm::dot(direction, zAxis);

        if (glm::abs(f) > 0.001f)
        {
            f32 t1 = (e + aabbMin.z) / f;
            f32 t2 = (e + aabbMax.z) / f;
            if (t1 > t2)
            {
                // Swap.
                f32 w = t1;
                t1 = t2;
                t2 = w;
            }
            if (t2 < tMax)
            {
                tMax = t2;
            }
            if (t1 > tMin)
            {
                tMin = t1;
            }
            if (tMax < tMin)
            {
                return false;
            }
        }
        else
        {
            if (aabbMin.z - e > 0.0f || aabbMax.z - e < 0.0f)
            {
                return false;
            }
        }
    }

    // @todo Normal.
    hit.tMin = tMin;
    hit.tMax = tMax;
    hit.point = origin + tMin * direction;

    return true;
}

bool Intersection::RayVsSphere(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& center, f32 radius, RayHitData& hit)
{
    glm::vec3 l = center - origin;
    f32 s = glm::dot(l, direction);
    f32 l2 = glm::dot(l, l);
    f32 r2 = radius * radius;

    // Miss.
    if (s < 0.0f && l2 > r2)
    {
        return false;
    }

    f32 s2 = s * s;
    f32 m2 = l2 - s2;

    // Miss.
    if (m2 > r2)
    {
        return false;
    }

    // A hit!
    f32 q = glm::sqrt(r2 - m2);
    if (l2 > s2)
    {
        hit.tMin = s - q;
        hit.tMax = s + q;
    }
    else
    {
        hit.tMin = s + q;
        hit.tMax = s - q;
    }
    hit.point = origin + hit.tMin * direction;
    hit.normal = glm::normalize(hit.point - center);
    return true;
}
} // namespace spy
