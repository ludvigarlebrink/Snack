#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace spy
{
class SKETCH_API SketchTree
{
public:

    static bool BeginNode(const std::string& label, bool isSelected, bool& isClicked);

    static bool BeginNode(const std::string& label, uint64 id, bool isSelected, bool& isClicked);

    static void EndNode();

    static bool LeafNode(const std::string& label, bool isSelected, bool& isClicked);

    static bool LeafNode(const std::string& label, uint64 id, bool isSelected, bool& isClicked);
};
} // namespace spy
