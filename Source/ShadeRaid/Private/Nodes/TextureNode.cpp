#include "Nodes/TextureNode.hpp"

namespace spy
{
TextureNode::~TextureNode()
{
}

std::string TextureNode::Compile()
{
    return "texture(someTexture, uv);"
}
} // namespace spy
