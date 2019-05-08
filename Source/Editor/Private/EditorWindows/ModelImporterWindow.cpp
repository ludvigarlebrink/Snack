#include "EditorWindows/ModelImporterWindow.hpp"
#include "EngineInclude.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchInclude.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

namespace snack
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
        Import();
    }
}

bool ModelImporterWindow::Import()
{
    uint32 flags = aiProcess_Triangulate;
    if (m_flipTextureCoordiantes)
    {
        flags |= aiProcess_FlipUVs;
    }

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(m_source, flags);
    if (!scene)
    {
        return false;
    }

    // Process the nodes recursively.
    ProcessNode(scene->mRootNode, scene);
}

void ModelImporterWindow::ProcessMesh(aiMesh* mesh)
{

}

void ModelImporterWindow::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (int32 i = 0; i < node->mNumMeshes; ++i)
    {
        ProcessMesh(node->mMeshes[i]);
    }

    for (int32 i = 0; i < node->mNumChildren; ++i)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}
} // namespace snack
