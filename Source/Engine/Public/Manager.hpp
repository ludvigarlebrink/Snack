#pragma once

#include "Managers/IAssetManager.hpp"
#include "Managers/IClassManager.hpp"
#include "Managers/IFileManager.hpp"
#include "Managers/IInputManager.hpp"
#include "Managers/IPhysics2DManager.hpp"
#include "Managers/IRenderManager.hpp"
#include "Managers/ISceneManager.hpp"
#include "Managers/IScriptManager.hpp"

namespace snack
{
class Engine;

class ENGINE_API Manager
{
    friend Engine;

public:

    static IAssetManager* Asset();

    static IClassManager* Class();

    static IFileManager* File();

    static IInputManager* Input();

    static IPhysics2DManager* Physics2D();

    static IRenderManager* Render();

    static ISceneManager* Scene();

    static IScriptManager* Script();

private:

    static IAssetManager* m_assetManager;
    static IClassManager* m_classManager;
    static IFileManager* m_fileManager;
    static IInputManager* m_inputManager;
    static IPhysics2DManager* m_physics2DManager;
    static IRenderManager* m_renderManager;
    static ISceneManager* m_sceneManager;
    static IScriptManager* m_scriptManager;
};
} // namespace snack
