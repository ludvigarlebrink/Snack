#pragma once

#include "BaseTypes.hpp"
#include "InstanceID.hpp"

#include <sol/sol.hpp>

namespace snack
{
class ENGINE_API ScriptObject final
{
public:

    ScriptObject(sol::state* state, const std::string& className, InstanceID id);

    ~ScriptObject();

    template <typename RetType = void, typename ...Args>
    void Call(const std::string& functionName, const Args& ...args);

    bool IsValid();

private:

    template <typename T, typename ...Args>
    static std::string ConvertArgsToLuaArgs(const T& t, const Args& ...args);

    template <typename T>
    static std::string ConvertArgsToLuaArgs(const T& t);

    static std::string ConvertArgsToLuaArgs(const std::string &str);

    static std::string ConvertArgsToLuaArgs(const char* str);

    static std::string ConvertArgsToLuaArgs();

    void SetUp();

    void TearDown();

private:

    bool m_isValid;

    std::string m_className;
    std::string m_objectName;
    sol::state* m_state;
    sol::table m_objectData;
    InstanceID m_id;
};
template<typename RetType, typename ...Args>
void ScriptObject::Call(const std::string& functionName, const Args& ...args)
{
    if (m_isValid && m_state)
    {
        std::string script = "return " + m_objectName + ":" + functionName + "(" + ConvertArgsToLuaArgs(args...) + ")";
        return static_cast<RetType>(m_state->script(script));
    }
}

template<typename T, typename ...Args>
std::string ScriptObject::ConvertArgsToLuaArgs(const T& t, const Args& ...args)
{
    return ConvertArgsToLuaArgs(t) + "," + ConvertArgsToLuaArgs(args...);
}

template<typename T>
inline std::string ScriptObject::ConvertArgsToLuaArgs(const T& t)
{
    return std::to_string(t);
}
} // namespace snack
