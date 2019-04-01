#pragma once

#include "EditorWindow.hpp"

namespace spy
{
class EDITOR_API TextureImporterWindow final : public EditorWindow
{
public:

    TextureImporterWindow();

    ~TextureImporterWindow();

protected:

    void OnDraw(f32 deltaTime) override;

private:

};
} // namespace spy
