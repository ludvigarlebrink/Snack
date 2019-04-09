#pragma once

#include "BaseTypes.hpp"

#include <glm/glm.hpp>
#include <string>

namespace snack
{
class SKETCH_API SketchWindow
{
public:

    static void BaseDockSpace();

    static bool Begin(const std::string& name);

    static bool BeginChild(const std::string& id);

    static bool BeginChild(const std::string& id, bool hasBorder);

    static bool BeginChild(const std::string& id, const glm::vec2& size);

    static bool BeginChild(const std::string& id, const glm::vec2& size, bool hasBorder);

    static void End();

    static void EndChild();

    static glm::vec2 GetPosition();

    static glm::vec2 GetSize();
};
} // namespace snack
