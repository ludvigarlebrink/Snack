#pragma once

#include <sol/sol.hpp>

namespace snack
{
class ENGINE_API ScriptObject final
{
public:

    ScriptObject();

    ~ScriptObject();

private:

    sol::table m_table;
};
} // namespace snack
