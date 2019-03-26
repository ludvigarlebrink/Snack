#include "EditorWindowManager.hpp"
#include "EditorWindows/EditorWindow.hpp"
#include "SketchInclude.hpp"

namespace spy
{
EditorWindowManager::EditorWindowManager()
{
}

EditorWindowManager::~EditorWindowManager()
{
}

EditorWindow* EditorWindowManager::GetWindow(const std::string& id)
{
    auto itr = m_openWindows.find(id);
    if (itr != m_openWindows.end())
    {
        return itr->second;
    }

    return nullptr;
}

bool EditorWindowManager::IsWindowOpen(const std::string& id)
{
    if (m_openWindows.find(id) != m_openWindows.end())
    {
        return true;
    }

    return false;
}

void EditorWindowManager::Tick(f32 deltaTime)
{
    for (auto w : m_openWindows)
    {
        SketchWindow::Begin(w.second->GetTitle());
        w.second->OnDraw(deltaTime);
        SketchWindow::End();
    }
}

void EditorWindowManager::OpenWindow(const std::string& id, EditorWindow* editorWindow)
{
    m_openWindows.insert({ id, editorWindow });
}
} // namespace spy
