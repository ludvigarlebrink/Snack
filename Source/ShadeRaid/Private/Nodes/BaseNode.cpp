#include "Nodes/BaseNode.hpp"

namespace spy
{
BaseNode::~BaseNode()
{
}

BaseNode* BaseNode::Next()
{
    return m_next;
}
} // namespace spy
