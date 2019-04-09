#pragma once

#include <string>

namespace snack
{
class SHADE_RAID_API BaseNode
{
public:

    virtual ~BaseNode();

    virtual std::string Compile() = 0;
    
    BaseNode* Next();

private:

    BaseNode* m_next;
};
} // namespace snack
