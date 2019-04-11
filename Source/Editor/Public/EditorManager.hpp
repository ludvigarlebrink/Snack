#pragma once

#include "Managers/IEditorSceneManager.hpp"
#include "Managers/IEditorWindowManager.hpp"

namespace snack
{
class Editor;

class EditorManager
{
    friend Editor;

public:

    static IEditorSceneManager* Scene();

    static IEditorWindowManager* Window();

private:

    static IEditorSceneManager* m_editorSceneManager;
    static IEditorWindowManager* m_editorWindowManager;
};
} // namespace snack
