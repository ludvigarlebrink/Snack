#pragma once

#include "BaseTypes.hpp"
#include "SkinnedVertex.hpp"
#include "StaticVertex.hpp"

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace snack
{
/**
 * @brief Graphic stream.
 */
class IGfxStream
{
public:

    enum Type : uint32
    {
        STATIC_MESH,
        SKINNED_MESH,
        JOINT
    };

    struct Header
    {
        char name[128];
        Type type;
        int32 id;
        int32 parentId;
        uint64 location;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };

public:

    virtual ~IGfxStream() = default;

    virtual void Close() = 0;

    virtual bool Open(const std::string& filepath) = 0;
};
} // namespace snack
