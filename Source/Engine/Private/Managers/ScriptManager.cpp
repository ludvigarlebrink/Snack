#include "ScriptManager.hpp"
#include "Manager.hpp"
#include "Transform.hpp"

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
    lua.do_file("Data/Player.lua");
    lua["Lemon"]["new"]();

    auto f = lua["Lemon"]["new"];
    if (f.valid())
    {
        f();
    }
}

void ScriptManager::PostTick(f32 deltaTime)
{

}

void ScriptManager::SetUp()
{
    // Open libraries.
    lua.open_libraries(sol::lib::base, sol::lib::package);

    SetUpMath();
    SetUpEngine();
}

void ScriptManager::SetUpEngine()
{
    lua.new_usertype<Transform>("Transform",
        "new", sol::no_constructor,

        "GetLocalPosition", &Transform::GetLocalPosition,
        "GetWorldPosition", &Transform::GetWorldPosition,

        "SetLocalPosition", sol::resolve<const glm::vec3&>(&Transform::SetLocalPosition),
        "SetLocalPosition", sol::resolve<f32, f32, f32>(&Transform::SetLocalPosition),
        "SetWorldPosition", sol::resolve<const glm::vec3&>(&Transform::SetWorldPosition),
        "SetWorldPosition", sol::resolve<f32, f32, f32>(&Transform::SetWorldPosition)
    );

    lua.set_function("Instantiate", sol::overload(
        []()->Transform* { return Manager::Scene()->Instantiate(); },
        [](Transform* parent)->Transform* { return Manager::Scene()->Instantiate(parent); }
    ));
}

void ScriptManager::SetUpMath()
{
    // Vec2.
    lua.new_usertype<glm::vec2>("Vec2",
        sol::constructors<
            glm::vec2(),
            glm::vec2(const glm::vec2&),
            glm::vec2(f32),
            glm::vec2(f32, f32)
        >(),

        // Properties.
        "x", &glm::vec2::x,
        "y", &glm::vec2::y,
        "r", &glm::vec2::r,
        "g", &glm::vec2::g
    );

    // Vec3.
    lua.new_usertype<glm::vec3>("Vec3",
        sol::constructors<
            glm::vec3(),
            glm::vec3(const glm::vec3&),
            glm::vec3(f32),
            glm::vec3(f32, f32, f32)
        >(),

        // Properties.
        "x", &glm::vec3::x,
        "y", &glm::vec3::y,
        "z", &glm::vec3::z,
        "r", &glm::vec3::r,
        "g", &glm::vec3::g,
        "b", &glm::vec3::b
    );

    // Vec3.
    lua.new_usertype<glm::vec4>("Vec4",
        sol::constructors<
        glm::vec4(),
        glm::vec4(const glm::vec4&),
        glm::vec4(f32),
        glm::vec4(f32, f32, f32, f32)
        >(),

        // Properties.
        "x", &glm::vec4::x,
        "y", &glm::vec4::y,
        "z", &glm::vec4::z,
        "w", &glm::vec4::w,
        "r", &glm::vec4::r,
        "g", &glm::vec4::g,
        "b", &glm::vec4::b,
        "a", &glm::vec4::a
    );
}

void ScriptManager::TearDown()
{
}
} // namespace snack
