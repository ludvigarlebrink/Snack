#include "Manager.hpp"

namespace snack
{
IAssetManager* Manager::m_assetManager = nullptr;
IClassManager* Manager::m_classManager = nullptr;
IFileManager* Manager::m_fileManager = nullptr;
IInputManager* Manager::m_inputManager = nullptr;
IPhysics2DManager* Manager::m_physics2DManager = nullptr;
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

IFileManager* Manager::File()
{
    return m_fileManager;
}

IInputManager* Manager::Input()
{
    return m_inputManager;
}

IPhysics2DManager* Manager::Physics2D()
{
    return nullptr;
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
