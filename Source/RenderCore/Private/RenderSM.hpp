#pragma once

#include "BaseTypes.hpp"

namespace spy
{
class RenderSM
{
public:

    static void BindArrayBuffer(uint32 vertexBuffer);

    static void BindElementBuffer(uint32 elementBuffer);

    static void BindTexture2D(uint32 texture2D);

    static void BindVertexArray(uint32 vertexArray);

    static void UseShaderProgram(uint32 shaderProgram);

private:

    static uint32 m_arrayBuffer;
    static uint32 m_elementBuffer;
    static uint32 m_shaderProgram;
    static uint32 m_texture2D;
    static uint32 m_vertexArray;
};
} // namespace spy
