#include "FullScreenQuad.hpp"
#include "glad/glad.h"

namespace spy
{
FullScreenQuad::FullScreenQuad()
{
    SetUp();
}

FullScreenQuad::~FullScreenQuad()
{
    TearDown();
}

void FullScreenQuad::Bind()
{
    glBindVertexArray(m_vao);
}

void FullScreenQuad::Render()
{
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FullScreenQuad::SetUp()
{
    f32 vertices[] = {
        // First triangle.
        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        
        // Second triangle.
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f,
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * 12, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(f32) * 2, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void FullScreenQuad::TearDown()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}
} // namespace spy
