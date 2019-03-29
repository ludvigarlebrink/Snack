#pragma once

#include "BaseTypes.hpp"

namespace spy
{
class SKETCH_API SketchNode
{
public:

    static void Begin(uint64 id);

    static void End();
};
} // namespace spy
