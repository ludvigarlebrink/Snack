#include "Scripting/ScriptObject.hpp"

namespace snack
{
ScriptObject::ScriptObject(sol::state* state, const std::string& className, InstanceID id)
    : m_isValid(false)
    , m_className(className)
    , m_state(state)
    , m_id(id)
{
    SetUp();
}

ScriptObject::~ScriptObject()
{
    TearDown();
}

bool ScriptObject::IsValid()
{
    return m_isValid;
}

std::string ScriptObject::ConvertArgsToLuaArgs(const std::string& str)
{
    return "\'" + str + "\'";
}

std::string ScriptObject::ConvertArgsToLuaArgs(const char* str)
{
    return ConvertArgsToLuaArgs(std::string(str));
}

std::string ScriptObject::ConvertArgsToLuaArgs()
{
    return "";
}

void ScriptObject::SetUp()
{
    m_objectName = m_className + "_" + std::to_string(m_id);
    std::string luaScript = m_objectName + " = " + m_className + ":new()";
    bool isValidCreation = true;
    m_state->script(luaScript, [&isValidCreation](lua_State* state, sol::protected_function_result result)
    {
        isValidCreation = false;
        return result;
    });

    if (isValidCreation)
    {
        m_objectData = (*m_state)[m_objectName];
        m_isValid = m_objectData.valid();
    }
}

void ScriptObject::TearDown()
{
    if (m_isValid && m_state)
    {
        m_state->do_string(m_objectName + " = nil");
    }
}
} // namespace snack
