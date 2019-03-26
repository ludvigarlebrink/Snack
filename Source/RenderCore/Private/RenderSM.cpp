#include "RenderSM.hpp"
#include "RenderError.hpp"
#include "glad/glad.h"

namespace spy
{
uint32 RenderSM::m_arrayBuffer = 0u;
uint32 RenderSM::m_elementBuffer = 0u;
uint32 RenderSM::m_shaderProgram = 0u;
uint32 RenderSM::m_texture2D = 0u;
uint32 RenderSM::m_vertexArray = 0u;

void RenderSM::BindArrayBuffer(uint32 arrayBuffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
    if (m_arrayBuffer != arrayBuffer)
    {
        SPY_CHECK_RENDER_ERROR();
        m_arrayBuffer = arrayBuffer;
    }
}

void RenderSM::BindElementBuffer(uint32 elementBuffer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    if (m_elementBuffer != elementBuffer)
    {
        SPY_CHECK_RENDER_ERROR();
        m_elementBuffer = elementBuffer;
    }
}

void RenderSM::BindTexture2D(uint32 texture2D)
{
    glBindTexture(GL_TEXTURE_2D, texture2D);
    if (m_texture2D != texture2D)
    {
        SPY_CHECK_RENDER_ERROR();
        m_texture2D = texture2D;
    }
}

void RenderSM::BindVertexArray(uint32 vertexArray)
{
    glBindVertexArray(vertexArray);
    if (m_vertexArray != vertexArray)
    {
        SPY_CHECK_RENDER_ERROR();
        m_vertexArray = vertexArray;
    }
}

void RenderSM::UseShaderProgram(uint32 shaderProgram)
{
    glUseProgram(shaderProgram);
    if (m_shaderProgram != shaderProgram)
    {
        SPY_CHECK_RENDER_ERROR();
        m_shaderProgram = shaderProgram;
    }
}
} // namespace spy
