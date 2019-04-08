#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace spy
{
class SKETCH_API SketchCombo
{
public:

    static bool Begin(const std::string& label, const std::string& previewLabel);
    
    static bool Begin(const std::string& label, const std::string& previewLabel, f32 width);

    static void End();

    static bool Selectable(const std::string& label);

    static bool Selectable(const std::string& label, bool isSelected);
};
} // namespace spy
