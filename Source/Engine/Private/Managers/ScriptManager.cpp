#include "ScriptManager.hpp"
#include "Components/Rendering/CameraComponent.hpp"
#include "Components/Rendering/DirectionalLightComponent.hpp"
#include "Components/Rendering/JointComponent.hpp"
#include "Components/Rendering/MeshComponent.hpp"
#include "Components/Rendering/PointLightComponent.hpp"
#include "Components/Rendering/SkinnedMeshComponent.hpp"
#include "Components/Rendering/SkyComponent.hpp"
#include "Components/Rendering/SpotlightComponent.hpp"
#include "Components/Rendering/TerrainComponent.hpp"
#include "Manager.hpp"
#include "Scripting/ScriptObject.hpp"
#include "Transform.hpp"

namespace snack
{
ScriptManager::ScriptManager()
    : m_state(nullptr)
    , m_nextInstanceID(0)
{
    SetUp();
}

ScriptManager::~ScriptManager()
{
    TearDown();
}

ScriptObject* ScriptManager::CreateBehaviorObject(const std::string& className)
{
    ScriptObject* scriptObject = new ScriptObject(m_state, className, m_nextInstanceID);
    if (scriptObject->IsValid())
    {
        ++m_nextInstanceID;
        m_behaviorObjects[className].push_back(scriptObject);
        return scriptObject;
    }

    delete scriptObject;
    return nullptr;
}

void ScriptManager::Tick(f32 deltaTime)
{
    m_state->do_file("Data/Player.lua");

    for (auto v : m_behaviorObjects)
    {
        for (auto s : v.second)
        {
            s->Call("OnTick", deltaTime);
        }
    }
}

void ScriptManager::PostTick(f32 deltaTime)
{
    for (auto v : m_behaviorObjects)
    {
        for (auto s : v.second)
        {
            s->Call("OnPostTick", deltaTime);
        }
    }
}

void ScriptManager::SetUp()
{
    m_state = new sol::state();

    // Open libraries.
    m_state->open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);

    std::string packagePath = (*m_state)["package"]["path"];
    (*m_state)["package"]["path"] = (packagePath + ";Data/middleclass.lua").c_str();

    SetUpMath();
    SetUpEngine();
}

void ScriptManager::SetUpEngine()
{
    m_state->new_usertype<Transform>("Transform",
        "new", sol::no_constructor,

        "AddComponent", &Transform::AddComponent,

        "GetLocalPosition", &Transform::GetLocalPosition,
        "GetWorldPosition", &Transform::GetWorldPosition,

        "RemoveComponent", &Transform::RemoveComponent,

        "SetLocalPosition", sol::resolve<const glm::vec3&>(&Transform::SetLocalPosition),
        "SetLocalPosition", sol::resolve<f32, f32, f32>(&Transform::SetLocalPosition),
        "SetWorldPosition", sol::resolve<const glm::vec3&>(&Transform::SetWorldPosition),
        "SetWorldPosition", sol::resolve<f32, f32, f32>(&Transform::SetWorldPosition)
    );

    // Rendering components.
    m_state->new_usertype<BaseComponent>("BaseComponent",
        "new", sol::no_constructor,
        "enabled", sol::property(&BaseComponent::IsEnabled, &BaseComponent::SetEnabled)
    );

    m_state->new_usertype<CameraComponent>("CameraComponent",
        sol::base_classes, sol::bases<BaseComponent>(),
        "new", sol::no_constructor,
        "fieldOfView", sol::property(&CameraComponent::GetFieldOfView, &CameraComponent::SetFieldOfView)
    );

    m_state->set_function("Instantiate", sol::overload(
        []()->Transform* { return Manager::Scene()->Instantiate(); },
        [](Transform* parent)->Transform* { return Manager::Scene()->Instantiate(parent); }
    ));
}

void ScriptManager::SetUpMath()
{
    // Vec2.
    m_state->new_usertype<glm::vec2>("Vec2",
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
    m_state->new_usertype<glm::vec3>("Vec3",
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
    m_state->new_usertype<glm::vec4>("Vec4",
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
