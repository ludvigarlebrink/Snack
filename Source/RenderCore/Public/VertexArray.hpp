#pragma once

#include "BaseTypes.hpp"

namespace snack
{
class RENDER_CORE_API VertexArray final
{
public:

    VertexArray();

    ~VertexArray();

private:

    uint32 m_vao;
};
} // namespace snack
