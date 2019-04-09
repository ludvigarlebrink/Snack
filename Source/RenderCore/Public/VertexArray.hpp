#pragma once

#include "BaseTypes.hpp"

namespace spy
{
class RENDER_CORE_API VertexArray final
{
public:

    VertexArray();

    ~VertexArray();

private:

    uint32 m_vao;
};
} // namespace spy
