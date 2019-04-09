#include "Editor.hpp"
#include "EditorWindows/AssetBrowserWindow.hpp"
#include "EditorWindows/GameWindow.hpp"
#include "EditorWindows/InspectorWindow.hpp"
#include "EditorWindows/MaterialEditorWindow.hpp"
#include "EditorWindows/SceneGraphWindow.hpp"
#include "EditorWindows/SceneWindow.hpp"
#include "EditorWindows/ScriptEditorWindow.hpp"
#include "EditorWindows/ShaderEditorWindow.hpp"
#include "EngineInclude.hpp"
#include "Managers/EditorSceneManager.hpp"
#include "Managers/EditorWindowManager.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"
#include "SketchInternal.hpp"
#include "Timer.hpp"

namespace snack
{
Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::Run()
{
    bool isRunning = true;

    Timer timer;
    while (isRunning)
    {
        f32 deltaTime = timer.GetElapsedSeconds();
        timer.Reset();
        EditorSceneManager* editorSceneManager = static_cast<EditorSceneManager*>(m_editorSceneManager);
        EditorWindowManager* editorWindowManager = static_cast<EditorWindowManager*>(m_editorWindowManager);

        Manager::Input()->ProcessEvents();

        // Rendering.
        RenderWindow* renderWindow = Manager::Render()->GetRenderWindow();
        renderWindow->Clear();
        SketchInternal::NewFrame(renderWindow);
        DrawMainMenu();
        SketchWindow::BaseDockSpace();
        editorWindowManager->Tick(deltaTime);

        isRunning = !SketchEvent::CloseRequest();
        
        SketchInternal::Render(renderWindow);
        renderWindow->Present();
    }
}

void Editor::SetUp()
{
    m_engine.SetUp();

    RenderWindow* renderWindow = Manager::Render()->GetRenderWindow();

    m_editorSceneManager = new EditorSceneManager;
    m_editorWindowManager = new EditorWindowManager;

    EditorManager::m_editorSceneManager = m_editorSceneManager;
    EditorManager::m_editorWindowManager = m_editorWindowManager;

    SketchInternal::SetUp(renderWindow);

    // Default windows.
    m_editorWindowManager->OpenWindow<AssetBrowserWindow>();
    m_editorWindowManager->OpenWindow<GameWindow>();
    m_editorWindowManager->OpenWindow<InspectorWindow>();
    m_editorWindowManager->OpenWindow<SceneWindow>();
    m_editorWindowManager->OpenWindow<SceneGraphWindow>();
}

void Editor::TearDown()
{
    SketchInternal::TearDown();
    m_engine.TearDown();
}

void Editor::DrawMainMenu()
{
    if (SketchMenu::BeginMain())
    {
        if (SketchMenu::Begin("File"))
        {
            if (SketchMenu::Item("Quit"))
            {

            }

            SketchMenu::End();
        }

        if (SketchMenu::Begin("Edit"))
        {
            if (SketchMenu::Item("Undo"))
            {

            }

            if (SketchMenu::Item("Redo"))
            {

            }

            Sketch::Seperator();

            if (SketchMenu::Item("Copy"))
            {

            }

            if (SketchMenu::Item("Cut"))
            {

            }

            if (SketchMenu::Item("Paste"))
            {

            }

            Sketch::Seperator();

            if (SketchMenu::Item("Duplicate"))
            {

            }

            if (SketchMenu::Item("Delete"))
            {

            }

            Sketch::Seperator();

            if (SketchMenu::Item("Begin Play"))
            {

            }

            if (SketchMenu::Item("Pause Play"))
            {

            }

            if (SketchMenu::Item("End Play"))
            {

            }

            SketchMenu::End();
        }

        if (SketchMenu::Begin("Window"))
        {
            if (SketchMenu::Item("Scene", "Ctrl+1"))
            {
                m_editorWindowManager->OpenWindow<SceneWindow>();
            }

            if (SketchMenu::Item("Game", "Ctrl+2"))
            {
                m_editorWindowManager->OpenWindow<GameWindow>();
            }

            if (SketchMenu::Item("Scene Graph", "Ctrl+3"))
            {
                m_editorWindowManager->OpenWindow<SceneGraphWindow>();
            }

            if (SketchMenu::Item("Inspector", "Ctrl+4"))
            {
                m_editorWindowManager->OpenWindow<InspectorWindow>();
            }

            if (SketchMenu::Item("Asset Browser", "Ctrl+5"))
            {
                m_editorWindowManager->OpenWindow<AssetBrowserWindow>();
            }

            if (SketchMenu::Item("Script Editor"))
            {
                m_editorWindowManager->OpenWindow<ScriptEditorWindow>();
            }

            if (SketchMenu::Item("Particle Editor"))
            {
                m_editorWindowManager->OpenWindow<ScriptEditorWindow>();
            }

            if (SketchMenu::Item("Material Editor"))
            {
                m_editorWindowManager->OpenWindow<MaterialEditorWindow>();
            }

            if (SketchMenu::Item("Shader Editor"))
            {
                m_editorWindowManager->OpenWindow<ShaderEditorWindow>();
            }

            SketchMenu::End();
        }

        if (SketchMenu::Begin("Help"))
        {
            if (SketchMenu::Item("Documentation"))
            {

            }

            SketchMenu::End();
        }

        SketchMenu::EndMain();
    }
}
} // namespace snack
