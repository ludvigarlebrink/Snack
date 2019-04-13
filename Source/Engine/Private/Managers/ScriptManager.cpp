#include "ScriptManager.hpp"

namespace snack
{
ScriptManager::ScriptManager()
{
    SetUp();
}

ScriptManager::~ScriptManager()
{
    TearDown();
}

void ScriptManager::Tick(f32 deltaTime)
{
}

void ScriptManager::PostTick(f32 deltaTime)
{
}

void ScriptManager::SetUp()
{
    // Open libraries.
    lua.open_libraries(sol::lib::base);

    SetUpMath();

    lua.script("v = vec2.new()\n"
        "v = vec2.new(12)\n"
        "v = vec2.new(10, 10)\n"
        "print(vec2.x)\n");
}

void ScriptManager::SetUpMath()
{
    // Vec2.
    {
        sol::constructors<glm::vec2(), glm::vec2(f32), glm::vec2(f32, f32)> ctor;
        sol::usertype<glm::vec2> utype = lua.new_usertype<glm::vec2>("vec2", ctor);
    //    utype["x"] = &glm::vec2::x;
    //    utype["y"] = &glm::vec2::y;
    //    utype["r"] = &glm::vec2::r;
    //    utype["g"] = &glm::vec2::g;
    }
}

void ScriptManager::TearDown()
{
}
} // namespace snack
