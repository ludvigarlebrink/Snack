#include "Nodes/TextureNode.hpp"

namespace snack
{
TextureNode::~TextureNode()
{
}

std::string TextureNode::Compile()
{
    return "texture(someTexture, uv);";
}
} // namespace snack
