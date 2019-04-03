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

        std::vector<std::string> MaterialList;
        MaterialList.push_back("Poop");
        MaterialList.push_back("Fabric");
        MaterialList.push_back("Death");

        
        Sketch::Text("Textures:");
        for (std::vector<std::string>::iterator it = MaterialList.begin(); it != MaterialList.end(); ++it)
        {
            Sketch::Text(*it);
            Sketch::SameLine();
            Sketch::Vec4Field("Color", m_color);
        }
        Sketch::Text("Is this working?!");
    }
}

void MaterialEditorWindow::SetColor(const glm::vec4 & color)
{
    m_color = color;
}

void MaterialEditorWindow::SetUp()
{
    m_material = new Material();
    m_material = Manager::Asset()->LoadMaterial(FileSystem::GetRelativeDataPath("Material/Poop.mat"));
}

void MaterialEditorWindow::TearDown()
{
}

} // namespace spy
