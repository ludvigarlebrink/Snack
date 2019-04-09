#include "Mesh.hpp"
#include "RenderSM.hpp"
#include "RenderError.hpp"
#include "glad/glad.h"

namespace snack
{
Mesh::Mesh()
    : m_vao(0u)
    , m_vbo(0u)
    , m_ebo(0u)
    , m_vertexSize(0)
    , m_vertexCount(0)
    , m_elementCount(0)
{
    glGenVertexArrays(1, &m_vao);
    SPY_CHECK_RENDER_ERROR();
    glGenBuffers(1, &m_vbo);
    SPY_CHECK_RENDER_ERROR();
    glGenBuffers(1, &m_ebo);
    SPY_CHECK_RENDER_ERROR();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
    SPY_CHECK_RENDER_ERROR();
    glDeleteBuffers(1, &m_vbo);
    SPY_CHECK_RENDER_ERROR();
    glDeleteBuffers(1, &m_ebo);
    SPY_CHECK_RENDER_ERROR();
}

void Mesh::Bind()
{
    RenderSM::BindVertexArray(m_vao);
    RenderSM::BindElementBuffer(m_ebo);
}

void Mesh::EnableAttribute(int32 index)
{
    Bind();
    glEnableVertexAttribArray(index);
    SPY_CHECK_RENDER_ERROR();
}

void* Mesh::MapForReading()
{
    Bind();
    void* returnVal = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    SPY_CHECK_RENDER_ERROR();
    return returnVal;
}

void* Mesh::MapForWriting()
{
    Bind();
    return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Mesh::Render(Mode mode)
{
    Bind();
    glDrawElements(ToGLMode(mode), m_elementCount, GL_UNSIGNED_INT, 0);
    SPY_CHECK_RENDER_ERROR();
}

void Mesh::Render(Mode mode, int32 count)
{
    Bind();
    glDrawElements(ToGLMode(mode), count, GL_UNSIGNED_INT, 0);
    SPY_CHECK_RENDER_ERROR();
}

void Mesh::Render(Mode mode, int32 count, void* offset)
{
    Bind();
    glDrawElements(ToGLMode(mode), count, GL_UNSIGNED_INT, offset);
    SPY_CHECK_RENDER_ERROR();
}

void Mesh::Reserve(int32 vertexCount, int32 vertexSize, int32 elementCount)
{
    SetData(NULL, vertexCount, vertexSize, NULL, elementCount, Optimization::STATIC_DRAW);
}

void Mesh::Reserve(int32 vertexCount, int32 vertexSize, int32 elementCount, Optimization optimization)
{
    SetData(NULL, vertexCount, vertexSize, NULL, elementCount, optimization);
}

void Mesh::SetAttribPtr(int32 index, Type type, int32 offset)
{
    Bind();
    switch (type)
    {
    case Type::F32:
        glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::INT32:
        glVertexAttribPointer(index, 1, GL_INT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC2:
        glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC2I:
        glVertexAttribPointer(index, 2, GL_INT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC2U:
        glVertexAttribPointer(index, 2, GL_UNSIGNED_INT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC3:
        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC3I:
        glVertexAttribPointer(index, 3, GL_INT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC3U:
        glVertexAttribPointer(index, 3, GL_UNSIGNED_INT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC4:
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC4I:
        glVertexAttribPointer(index, 4, GL_INT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC4U:
        glVertexAttribPointer(index, 4, GL_UNSIGNED_INT, GL_FALSE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    case Type::VEC4UB:
        glVertexAttribPointer(index, 4, GL_UNSIGNED_BYTE, GL_TRUE, m_vertexSize, reinterpret_cast<void*>(offset));
        break;
    default:
        break;
    }

    SPY_CHECK_RENDER_ERROR();
}

void Mesh::SetData(void* vertexData, int32 vertexCount, int32 vertexSize, uint32* elementData, int32 elementCount)
{
    SetData(vertexData, vertexSize, vertexCount, elementData, elementCount, Optimization::STATIC_DRAW);
}

void Mesh::SetData(void* vertexData, int32 vertexCount, int32 vertexSize, uint32* elementData, int32 elementCount, Optimization optimization)
{
    m_vertexSize = vertexSize;
    m_vertexCount = vertexCount;
    m_elementCount = elementCount;

    RenderSM::BindVertexArray(m_vao);
    uint32 glOptimization = ToGLOptimization(optimization);

    RenderSM::BindArrayBuffer(m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexCount, vertexData, glOptimization);
    SPY_CHECK_RENDER_ERROR();

    RenderSM::BindElementBuffer(m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * elementCount, elementData, glOptimization);
    SPY_CHECK_RENDER_ERROR();
}

void Mesh::SetVertexSubData(void* vertexData, int32 count, int32 offset)
{
    RenderSM::BindArrayBuffer(m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, offset, count * m_vertexSize, vertexData);
    SPY_CHECK_RENDER_ERROR();
}

void Mesh::SetElementSubData(uint32* elementData, int32 count, int32 offset)
{
    RenderSM::BindElementBuffer(m_ebo);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, count * sizeof(uint32), elementData);
    SPY_CHECK_RENDER_ERROR();
}

void Mesh::Unmap()
{
    glUnmapBuffer(GL_ARRAY_BUFFER);
    SPY_CHECK_RENDER_ERROR();
}

uint32 Mesh::ToGLMode(Mode mode)
{
    switch (mode)
    {
    case Mode::LINE_LOOP:
        return GL_LINE_LOOP;
    case Mode::LINE_STRIP:
        return GL_LINE_STRIP;
    case Mode::LINE_STRIP_ADJACENCY:
        return GL_LINE_STRIP_ADJACENCY;
    case Mode::LINES:
        return GL_LINES;
    case Mode::LINES_ADJACENCY:
        return GL_LINES_ADJACENCY;
    case Mode::PATCHES:
        return GL_PATCHES;
    case Mode::POINTS:
        return GL_POINTS;
    case Mode::TRIANGLE_FAN:
        return GL_TRIANGLE_FAN;
    case Mode::TRIANGLE_STRIP:
        return GL_TRIANGLE_STRIP;
    case Mode::TRIANGLE_STRIP_ADJACENCY:
        return GL_TRIANGLE_STRIP_ADJACENCY;
    case Mode::TRIANGLES:
        return GL_TRIANGLES;
    case Mode::TRIANGLES_ADJACENCY:
        return GL_TRIANGLES_ADJACENCY;
    default:
        break;
    }

    return GL_TRIANGLES;
}

uint32 Mesh::ToGLOptimization(Optimization optimization)
{
    switch (optimization)
    {
    case Optimization::DYNAMIC_DRAW:
        return GL_DYNAMIC_DRAW;
    case Optimization::STATIC_DRAW:
        return GL_STATIC_DRAW;
    case Optimization::STREAM_DRAW:
        return GL_STREAM_DRAW;
    default:
        break;
    }

    return GL_STATIC_DRAW;
}
} // namespace snack
