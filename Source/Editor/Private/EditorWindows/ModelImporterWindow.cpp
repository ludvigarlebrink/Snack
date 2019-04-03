#include "EditorWindows/ModelImporterWindow.hpp"
#include "EngineInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

#include <iostream>

namespace spy
{
ModelImporterWindow::ModelImporterWindow()
    : m_flipTextureCoordiantes(false)
    , m_generateNormals(false)
    , m_generateTangents(false)
{
}

ModelImporterWindow::~ModelImporterWindow()
{
}

std::string ModelImporterWindow::GetTitle()
{
    return "Model Importer";
}

void ModelImporterWindow::SetFile(const std::string& source)
{
    m_source = source;
}

void ModelImporterWindow::OnDraw(f32 deltaTime)
{
    if (m_source.empty())
    {
        Sketch::Text("Select file to import!");
    }

    Sketch::Checkbox("Flip Texture Coordiantes", m_flipTextureCoordiantes);
    Sketch::Checkbox("Generate Normals", m_generateNormals);
    Sketch::Checkbox("Generate Tangents", m_generateTangents);

    if (Sketch::Button("Import"))
    {
        std::string extension = m_source.substr(m_source.find_last_of('.'));
        if (extension == ".obj")
        {
            ImportObj();
        }
        else if (extension == ".fbx")
        {
            // @todo fbx support.
        }
    }
}

void ModelImporterWindow::ImportObj()
{
    // Converting it to our format.
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoordianates;
    std::vector<uint32> elements;
    ObjParser objParser;
    if (objParser.Parse(m_source, positions, normals, textureCoordianates, elements))
    {
        std::vector<StaticVertex> vertices(positions.size());
        for (int32 i = 0; i < positions.size(); ++i)
        {
            vertices[i].position = positions[i];
            if (i < normals.size())
            {
                vertices[i].normal = normals[i];
            }
            else
            {
                vertices[i].normal = glm::vec3(0.0f, 0.0f, 1.0f);
            }

            if (i < textureCoordianates.size())
            {
                vertices[i].textureCoordinate = textureCoordianates[i];
            }
            else
            {
                vertices[i].textureCoordinate = glm::vec2(0.0f, 0.0f);
            }
        }

        std::cout << "Model: " << m_source << " imported.\n";
    }
}
} // namespace spy
