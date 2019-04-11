#pragma once

#include "BaseTypes.hpp"
#include "Managers/IEditorWindowManager.hpp"

#include <unordered_map>

namespace snack
{
class EditorWindowManager final : public IEditorWindowManager
{
public:

    EditorWindowManager();

    ~EditorWindowManager();

    EditorWindow* GetWindow(const std::string& id) override;

    bool IsWindowOpen(const std::string& id) override;

    void Tick(f32 deltaTime);

protected:

    void OpenWindow(const std::string& id, EditorWindow* editorWindow) override;

private:

    std::unordered_map<std::string, EditorWindow*> m_openWindows;
};
} // namespace snack
