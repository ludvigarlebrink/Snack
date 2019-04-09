#include "Nodes/BaseNode.hpp"

namespace snack
{
BaseNode::~BaseNode()
{
}

BaseNode* BaseNode::Next()
{
    return m_next;
}
} // namespace snack
