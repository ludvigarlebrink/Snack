#pragma once

#include "BaseTypes.hpp"
#include "Managers/IAssetManager.hpp"
#include "Managers/IClassManager.hpp"
#include "Managers/IInputManager.hpp"
#include "Managers/IRenderManager.hpp"
#include "Managers/ISceneManager.hpp"

#include <string>
#include <unordered_map>
#include <iostream>

namespace snack
{
class BehaviorComponent;
class BehaviorSystem;
class InputSystem;
class Physics2DSystem;
class RenderSystem;
class SoundSystem;
class Transform;

class ENGINE_API Engine final
{
public:

    Engine();

    ~Engine();

    void Run();

    void SetUp();

    void TearDown();

private:

    IAssetManager* m_assetManager;
    IClassManager* m_classManager;
    IInputManager* m_inputManager;
    IRenderManager* m_renderManager;
    ISceneManager* m_sceneManager;
};
} // namespace snack
