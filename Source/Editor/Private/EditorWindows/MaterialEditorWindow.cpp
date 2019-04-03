#include "EditorWindows/MaterialEditorWindow.hpp"
#include "EngineInclude.hpp"
#include "FileSystem.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

namespace spy
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

        std::vector<std::string> TextureList;
        TextureList = m_material->GetIds();
        /*TextureList.push_back("Poop");
        TextureList.push_back("Fabric");
        TextureList.push_back("Death");

        glm::vec4 Initcolor(0.0, 0.0, 0.0, 0.0);
        for (int x = 0; x < TextureList.size(); ++x)
        {
            m_colors.push_back(Initcolor);
        }*/
        //Sketch::Vec4Field("Color", m_color);
        Sketch::Text("Textures:");
        int y = 0;
        for (std::vector<std::string>::iterator it = TextureList.begin(); it != TextureList.end(); ++it)
        {
            Sketch::Text(*it);
            Sketch::SameLine();
            Sketch::Vec4Field("Color", m_colors[y]);
            y++;
        }
        Sketch::Text("Is this working?!");
    }
}

void MaterialEditorWindow::SetColor(const std::vector<glm::vec4>& colors, const glm::vec4 color)
{
    m_color = color;
    m_colors = colors;
    for (std::vector<glm::vec4>::iterator it = m_colors.begin(); it != m_colors.end(); ++it)
    {
        m_colors.push_back(m_color);
    }  
}

void MaterialEditorWindow::SetUp()
{
    m_material = new Material();
    m_material = Manager::Asset()->LoadMaterial(FileSystem::GetRelativeDataPath("Material/Default.mat"));
}

void MaterialEditorWindow::TearDown()
{
}

} // namespace spy
