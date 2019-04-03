#include "EditorWindows\TextureImporterWIndow.hpp"
#include "SketchInclude.hpp"

namespace spy
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

void TextureImporterWindow::SetFile(const std::string& filename)
{
}

void TextureImporterWindow::OnDraw(f32 deltaTime)
{
    Sketch::Text("File: ");

    if (Sketch::Button("Import"))
    {

    }
}
} // namespace spy
