#pragma once

#include "EditorWindow.hpp"

namespace spy
{
class EDITOR_API ModelImporterWindow final : public EditorWindow
{
public:

    ModelImporterWindow();

    ~ModelImporterWindow();

protected:

    void OnDraw(f32 deltaTime) override;

private:


};
} // namespace spy
