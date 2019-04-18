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

    /**
     * @brief End the source.
     */
    static void EndSource();

    /**
     * @brief Ends the target.
     */
    static void EndTarget();

    /**
     * @brief Set a drag n drop payload.
     */
    static void SetPayload(const std::string& type, void* data);

    /**
     * @brief Set a drag n drop payload.
     */
    static void SetPayload(const std::string& type, void* data, uint64 size);

    /**
     * @brief Quick drag n drop for texts.
     */
    static bool TextSource(const std::string& label, const std::string& type, const std::string& data);

    static bool TextTarget(const std::string& type, std::string& data);
};
} // namespace snack

/**
 * @class snack::SketchDragDrop
 * @ingroup Sketch
 */
