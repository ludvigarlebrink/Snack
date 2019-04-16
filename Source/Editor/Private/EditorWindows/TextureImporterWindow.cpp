#include "EditorWindows\TextureImporterWIndow.hpp"
#include "SketchInclude.hpp"

namespace snack
{
TextureImporterWindow::TextureImporterWindow()
{
}

TextureImporterWindow::~TextureImporterWindow()
{
}

std::string TextureImporterWindow::GetTitle()
{
    return "Texture Importer";
}

void TextureImporterWindow::SetFile(const std::string& filepath)
{
}

void TextureImporterWindow::OnDraw(f32 deltaTime)
{
    Sketch::Text("File: ");

    if (Sketch::Button("Import"))
    {

    }
}
} // namespace snack
