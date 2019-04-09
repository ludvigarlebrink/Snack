#pragma once

#include "BaseTypes.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace snack
{
class SKETCH_API SketchGizmo
{
public:

    static void Cone(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& rightAxis, f32 baseScaling, f32 topScaling);

    static void Cone(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& rightAxis, f32 baseScaling, f32 topScaling, const glm::vec4& color);

    static void ConeOverdrawn(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& rightAxis, f32 baseScaling, f32 topScaling);

    static void ConeOverdrawn(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& rightAxis, f32 baseScaling, f32 topScaling, const glm::vec4& color);

    static void Cube(const glm::mat4& model);
    
    static void Cube(const glm::mat4& model, const glm::vec4& color);

    static void CubeOverdrawn(const glm::mat4& model);
    
    static void CubeOverdrawn(const glm::mat4& model, const glm::vec4& color);

    static void Line(const glm::vec3& p0, glm::vec3& p1);

    static void Line(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color);

    static void LineOverdrawn(const glm::vec3& p0, glm::vec3& p1);

    static void LineOverdrawn(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color);

    static void Quad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);

    static void Quad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color);

    static void QuadOverdrawn(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);

    static void QuadOverdrawn(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color);
};
} // namespace snack
