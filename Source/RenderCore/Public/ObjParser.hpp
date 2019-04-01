#pragma once

#include "BaseTypes.hpp"

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace spy
{
class RENDER_CORE_API ObjParser
{
public:

    static bool Parse(const std::string& filename, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals,
        std::vector<glm::vec2>& textureCoordiantes, std::vector<uint32>& elements);

private:


};
} // namespace spy
