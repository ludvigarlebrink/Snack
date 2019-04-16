#pragma once

#include "EditorWindow.hpp"

namespace snack
{
class EDITOR_API TextureImporterWindow final : public EditorWindow
{
public:

    TextureImporterWindow();

    ~TextureImporterWindow();

    std::string GetTitle() override;

    void SetFile(const std::string& filepath);

protected:

    void OnDraw(f32 deltaTime) override;

private:

};
} // namespace snack
