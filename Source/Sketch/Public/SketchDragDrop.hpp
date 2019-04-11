#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace snack
{
/**
 * @brief Drag and drop.
 */
class SKETCH_API SketchDragDrop
{
public:

    struct Payload
    {
        uint64 size = 0u;
        void* data = nullptr;
    };

public:

    static bool AcceptPayload(const std::string& type, Payload& payload);

    static bool BeginSource();

    static bool BeginSource(const std::string& label);

    static bool BeginTarget();

    static void EndSource();

    static void EndTarget();

    static void SetPayload(const std::string& type, void* data);

    static void SetPayload(const std::string& type, void* data, uint64 size);
};
} // namespace snack

/**
 * @class snack::SketchDragDrop
 * @ingroup Sketch
 */
