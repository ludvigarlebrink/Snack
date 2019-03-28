#pragma once

#include "BaseNode.hpp"

namespace spy
{
/**
 * @brief A texture node.
 */
class SHADE_RAID_API TextureNode final : public BaseNode
{
public:

    ~TextureNode();

    std::string Compile();

private:

};
} // namespace spy
