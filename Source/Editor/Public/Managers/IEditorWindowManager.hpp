#pragma once

#include <typeinfo>
#include <string>

namespace spy
{
class EditorWindow;

class IEditorWindowManager
{
public:

    virtual ~IEditorWindowManager() = default;

    virtual EditorWindow* GetWindow(const std::string& id) = 0;

    virtual bool IsWindowOpen(const std::string& id) = 0;

    template <typename T>
    T* OpenWindow();

protected:

    virtual void OpenWindow(const std::string& id, EditorWindow* editorWindow) = 0;
};

template<typename T>
T* IEditorWindowManager::OpenWindow()
{
    std::string id = typeid(T).name();
    T* editorWindow = static_cast<T*>(GetWindow(id));
    if (!editorWindow)
    {
        T* newEditorWindow = new T();
        OpenWindow(id, newEditorWindow);
        return newEditorWindow;
    }

    return editorWindow;
}
} // namespace spy
