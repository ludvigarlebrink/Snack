#pragma once

#include "EditorWindow.hpp"

namespace spy
{
class EDITOR_API TextureImporterWindow final : public EditorWindow
{
public:

    TextureImporterWindow();

    ~TextureImporterWindow();

    std::string GetTitle() override;

    void SetFile(const std::string& filename);

protected:

    void OnDraw(f32 deltaTime) override;

private:

};
} // namespace spy
