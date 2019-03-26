#pragma once

#include "Engine.hpp"
#include "EngineForward.hpp"
#include "EditorManager.hpp"

namespace spy
{
class EDITOR_API Editor final
{
public:

    Editor();

    ~Editor();

    void Run();
    
    void SetUp();

    void TearDown();

private:

    void DrawMainMenu();

private:

    Engine m_engine;

    IEditorSceneManager* m_editorSceneManager;
    IEditorWindowManager* m_editorWindowManager;
};
} // namespace spy
