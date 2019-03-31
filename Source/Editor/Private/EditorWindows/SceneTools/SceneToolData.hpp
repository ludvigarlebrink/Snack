#pragma once

#include "SceneToolData.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace spy
{
struct SceneToolData
{
    bool cameraMode;
    int32 width;
    int32 height;
    glm::vec3 cameraPosition;
    glm::mat4 projection;
    glm::mat4 viewInverse;
};
} // namespace spy
