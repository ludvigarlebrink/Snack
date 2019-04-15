#include "EditorWindows/MaterialEditorWindow.hpp"
#include "EngineInclude.hpp"
#include "FileSystem.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

namespace snack
{
MaterialEditorWindow::MaterialEditorWindow()
    : m_material(nullptr)
{
    SetUp();
}

MaterialEditorWindow::~MaterialEditorWindow()
{
    TearDown();
}

std::string MaterialEditorWindow::GetTitle()
{
    return "Material Editor";
}

void MaterialEditorWindow::OnDraw(f32 deltaTime)
{   
    if (m_material)
    {
        bool isMaterial = false;
        glm::vec4 colorz;

        std::vector<std::string> textureList;
        textureList = m_material->GetIds();

        Sketch::Text("Textures:");
        for (auto& it : textureList)
        {
            Sketch::Text(it);
            Sketch::SameLine();
            colorz = m_material->GetColor(it);
            Sketch::Vec4Field("Color", colorz);
        }
    }
}

void MaterialEditorWindow::SetColor(const std::vector<glm::vec4>& colors, const glm::vec4 color)
{
    m_color = color;
     
}

void MaterialEditorWindow::SetUp()
{
    m_material = new Material();
    m_material = Manager::Asset()->LoadMaterial("Materials/Default.mat");
}

void MaterialEditorWindow::TearDown()
{
}
} // namespace snack
