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

        std::vector<std::string> textureList;
        textureList = m_material->GetIds();

        Sketch::Text("Textures:");
        int32 y = 0;
        for (auto& it : textureList)
        {
            Sketch::Text(it);
            Sketch::SameLine();
            m_color = m_material->GetColor(*it);
            Sketch::Vec4Field("Color", m_color);
            y++;
        }
        Sketch::Text("Is this working?!");
    }
}

void MaterialEditorWindow::SetColor(const std::vector<glm::vec4>& colors, const glm::vec4 color)
{
    m_color = color;
    /*m_colors = colors;
    for (std::vector<glm::vec4>::iterator it = m_colors.begin(); it != m_colors.end(); ++it)
    {
        m_colors.push_back(m_color);
    } */ 
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
