#pragma once

#include "Managers/IEditorProjectManager.hpp"

namespace snack
{
class EditorProjectManager final : public IEditorProjectManager
{
public:

    EditorProjectManager();

    ~EditorProjectManager();

    bool Load(const std::string& filepath) override;

private:


};
} // namespace snack
