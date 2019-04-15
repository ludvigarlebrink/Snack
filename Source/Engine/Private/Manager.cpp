#include "Manager.hpp"

namespace snack
{
IAssetManager* Manager::m_assetManager = nullptr;
IClassManager* Manager::m_classManager = nullptr;
IInputManager* Manager::m_inputManager = nullptr;
IRenderManager* Manager::m_renderManager = nullptr;
ISceneManager* Manager::m_sceneManager = nullptr;
IScriptManager* Manager::m_scriptManager = nullptr;

IAssetManager* Manager::Asset()
{
    return m_assetManager;
}

IClassManager* Manager::Class()
{
    return m_classManager;
}

IInputManager* Manager::Input()
{
    return m_inputManager;
}

IRenderManager* Manager::Render()
{
    return m_renderManager;
}

ISceneManager* Manager::Scene()
{
    return m_sceneManager;
}

IScriptManager* Manager::Script()
{
    return m_scriptManager;
}
} // namespace snack
