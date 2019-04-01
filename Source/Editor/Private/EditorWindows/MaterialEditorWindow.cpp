#include"EditorWindows/MaterialEditorWindow.hpp"
#include "EngineInclude.hpp"
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
        std::string temp;

        std::vector<std::string> MaterialList;
        MaterialList.push_back("Poop");
        MaterialList.push_back("Fabric");
        MaterialList.push_back("Death");

        //MaterialList = m_material->GetIds();
        
        glm::vec4 color(0.00, 0.00, 0.00, 0.00);
        glm::vec4 texture(0.00, 0.00, 0.00, 0.00);
        Sketch::Text("Textures:");
        for (std::vector<std::string>::iterator it = MaterialList.begin(); it != MaterialList.end(); ++it)
        {
            Sketch::Checkbox(*it, isMaterial);
            Sketch::SameLine();
            Sketch::Vec4Field("Color", color);
        }
        Sketch::Text("Is this working?!");
    }
}



void MaterialEditorWindow::SetUp()
{
    m_material = new Material();
}

void MaterialEditorWindow::TearDown()
{
}
} // namespace spy
