#pragma once

#include "BaseTypes.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace spy
{
class SKETCH_API SketchGizmo
{
public:

    static void Line(const glm::vec3& p0, glm::vec3& p1);

    static void Line(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color);

    static void LineOverdrawn(const glm::vec3& p0, glm::vec3& p1);

    static void LineOverdrawn(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color);
};
} // namespace spy
