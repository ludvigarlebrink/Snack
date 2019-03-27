#pragma once

#include "Managers/IAssetManager.hpp"
#include "Managers/IClassManager.hpp"
#include "Managers/IInputManager.hpp"
#include "Managers/IRenderManager.hpp"
#include "Managers/ISceneManager.hpp"

namespace spy
{
class Engine;

class ENGINE_API Manager
{
    friend Engine;

public:

    static IAssetManager* Asset();

    static IClassManager* Class();

    static IInputManager* Input();

    static IRenderManager* Render();

    static ISceneManager* Scene();

private:

    static IAssetManager* m_assetManager;
    static IClassManager* m_classManager;
    static IInputManager* m_inputManager;
    static IRenderManager* m_renderManager;
    static ISceneManager* m_sceneManager;
};
} // namespace spy