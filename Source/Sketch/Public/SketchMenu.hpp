#pragma once

#include <string>

namespace spy
{
class SKETCH_API SketchMenu
{
public:

    static bool Begin(const std::string& label);

    static bool BeginMain();

    static void End();

    static void EndMain();

    static bool Item(const std::string& label);

    static bool Item(const std::string& label, bool enabled);

    static bool Item(const std::string& label, const std::string& shortcut);

};
} // namespace spy
