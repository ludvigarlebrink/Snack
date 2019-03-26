#include "Engine.hpp"
#include "Manager.hpp"
#include "Managers/AssetManager.hpp"
#include "Managers/ClassManager.hpp"
#include "Managers/InputManager.hpp"
#include "Managers/RenderManager.hpp"
#include "Managers/SceneManager.hpp"
#include "RenderCoreInclude.hpp"
#include "UtilsInclude.hpp"

// @todo hack
#include "Components/Behavior/BehaviorComponent.hpp"
#include "Components/Input/InputComponent.hpp"

// Rendering.
#include "Components/Rendering/CameraComponent.hpp"
#include "Components/Rendering/DirectionalLightComponent.hpp"
#include "Components/Rendering/JointComponent.hpp"
#include "Components/Rendering/MeshComponent.hpp"
#include "Components/Rendering/PointLightComponent.hpp"
#include "Components/Rendering/SkinnedMeshComponent.hpp"
#include "Components/Rendering/SpotlightComponent.hpp"


#include <iostream>

namespace spy
{
Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
    bool isRunning = true;
    Timer timer;
    f32 deltaTime = 0.0f;
    f32 fixedDeltaTime = 0.1f;
    f32 fixedDeltaTimeCounter = 0.0f;

    while (isRunning)
    {
        deltaTime = timer.GetElapsedSeconds();
        timer.Reset();
    }
}

void Engine::SetUp()
{
    // Create the managers.
    m_assetManager = new AssetManager();
    m_classManager = new ClassManager();
    m_inputManager = new InputManager();
    m_renderManager = new RenderManager();
    m_sceneManager = new SceneManager();

    Manager::m_assetManager = m_assetManager;
    Manager::m_classManager = m_classManager;
    Manager::m_inputManager = m_inputManager;
    Manager::m_renderManager = m_renderManager;
    Manager::m_sceneManager = m_sceneManager;

    m_classManager->RegisterComponentUnconstructable<BehaviorComponent>("Behavior");
    m_classManager->RegisterComponent<InputComponent>("Input");

    // Rendering.
    m_classManager->RegisterComponent<CameraComponent>("Camera");
    m_classManager->RegisterComponent<DirectionalLightComponent>("Directional Light");
    m_classManager->RegisterComponent<JointComponent>("Joint");
    m_classManager->RegisterComponent<MeshComponent>("Mesh");
    m_classManager->RegisterComponent<PointLightComponent>("Point Light");
    m_classManager->RegisterComponent<SkinnedMeshComponent>("Skinned Mesh");
    m_classManager->RegisterComponent<SpotlightComponent>("Spotlight");
}

void Engine::TearDown()
{
    // @todo
}
} // namespace spy
