#include "EditorWindows/AssetBrowserWindow.hpp"
#include "EditorManager.hpp"
#include "EditorWindows/ModelImporterWindow.hpp"
#include "EditorWindows/TextureImporterWindow.hpp"
#include "EditorWindows/TerrainEditorWindow.hpp"
#include "EngineInclude.hpp"
#include "PlatformInclude.hpp"
#include "SketchInclude.hpp"

#include <iostream>

namespace snack
{
AssetBrowserWindow::AssetBrowserWindow()
    : m_refresh(false)
    , m_selectedFolder(nullptr)
    , m_data(nullptr)
    , m_editorData(nullptr)
{
    SetUp();
}

AssetBrowserWindow::~AssetBrowserWindow()
{
    TearDown();
}

std::string AssetBrowserWindow::GetTitle()
{
    return "Asset Browser";
}

void AssetBrowserWindow::OnDraw(f32 deltaTime)
{
    if (m_refresh)
    {
        Refresh();
        m_refresh = false;
    }

    if (SketchEvent::DropFile())
    {
        std::string filepath = SketchEvent::DropFilename();
        std::string extension = filepath.substr(filepath.find_last_of('.'));
        if (extension == ".obj" || extension == ".fbx")
        {
            ModelImporterWindow* modelImporter = EditorManager::Window()->OpenWindow<ModelImporterWindow>();
            modelImporter->SetFile(filepath);
        }

        if (extension == ".png" || extension == ".bmp" || extension == ".jpg" || extension == ".jpeg")
        {
            TextureImporterWindow* textureImporter = EditorManager::Window()->OpenWindow<TextureImporterWindow>();

        }
    }

    SketchWindow::BeginChild("AssetBrowserTreeView", glm::vec2(200.0f, 0.0f));
    {
        DrawFolderNode(m_data);
        DrawFolderNode(m_editorData);
    }
    SketchWindow::EndChild();

    Sketch::SameLine();

    SketchWindow::BeginChild("AssetBrowserFileView");
    {
        if (Sketch::Button("Import"))
        {
            m_refresh = true;
        }

        Sketch::SameLine();

        if (Sketch::Button("Refresh"))
        {
            m_refresh = true;
        }

        Sketch::SameLine();

        Sketch::TextField("Search", m_search);

        Sketch::Seperator();

        if (m_selectedFolder)
        {
            for (int32 i = 0; i < m_selectedFolder->GetFileInfoCount(); ++i)
            {
                FolderNode::FileInfo& fileInfo = m_selectedFolder->GetFileInfo(i);
                if (m_search.empty() || m_search == fileInfo.name.substr(0, m_search.length()))
                {
                    bool isSelected = false;
                    int32 selectedIndex = 0;
                    for (int32 j = 0; j < m_selectedFiles.size(); ++j)
                    {
                        if (m_selectedFiles[j] == i)
                        {
                            isSelected = true;
                            selectedIndex = j;
                            break;
                        }
                    }

                    bool isClicked = Sketch::Selectable(fileInfo.name + fileInfo.extension, isSelected);
                    if (isClicked)
                    {
                        if (SketchEvent::ModRepeat(Mod::SHIFT))
                        {
                            if (isSelected)
                            {
                                m_selectedFiles.erase(m_selectedFiles.begin() + selectedIndex);
                            }
                            else
                            {
                                m_selectedFiles.push_back(i);
                            }
                        }
                        else
                        {
                            if (isSelected)
                            {
                                m_selectedFiles.clear();
                            }
                            else
                            {
                                m_selectedFiles.clear();
                                m_selectedFiles.push_back(i);
                            }
                        }
                    }
                }

                if (SketchDragDrop::BeginSource(fileInfo.name))
                {
                    // @todo This is a bit clunky, maybe make this better?
                    char filepath[512];
                    memset(filepath, '\0', 512);
                    memcpy(filepath, fileInfo.relativePath.c_str(), fileInfo.relativePath.size());
                    SketchDragDrop::SetPayload("Filename", filepath, 512);
                    SketchDragDrop::EndSource();
                }

                if (SketchPopup::BeginContext(fileInfo.name + fileInfo.extension))
                {
                    if (fileInfo.extension == ".scn")
                    {
                        if (SketchMenu::Item("Open"))
                        {
                            // @todo Check if the current scene is saved?
                            // Load the scene.
                            Manager::Scene()->Load(fileInfo.relativePath);
                        }
                        Sketch::Seperator();
                    }
                    else if (fileInfo.extension == ".mt")
                    {
                        SketchMenu::Item("Open");
                        Sketch::Seperator();
                    }
                    else if (fileInfo.extension == ".shader")
                    {
                        SketchMenu::Item("Open");
                        Sketch::Seperator();
                    }
                    else if (fileInfo.extension == ".trn")
                    {
                        if (SketchMenu::Item("Open"))
                        {
                            TerrainEditorWindow* terrainWindow = EditorManager::Window()->OpenWindow<TerrainEditorWindow>();
                            terrainWindow->SetTerrain(fileInfo.fullRelativePath);
                        }
                        Sketch::Seperator();
                    }

                    if (SketchMenu::Item("Delete"))
                    {
                        FileSystem::DeleteFile(fileInfo.fullRelativePath);
                        m_refresh = true;
                    }
                    
                    if (SketchMenu::Item("Rename"))
                    {

                    }

                    SketchPopup::End();
                }

            }
        }
    }
    SketchWindow::EndChild();
}

void AssetBrowserWindow::DrawFolderNode(FolderNode* folderNode)
{
    bool isOpen = false;
    bool isClicked = false;
    bool isSelected = m_selectedFolder == folderNode;
    if (folderNode->IsLeaf())
    {
        isOpen = SketchTree::LeafNode(folderNode->GetName(), isSelected, isClicked);
    }
    else
    {
        isOpen = SketchTree::BeginNode(folderNode->GetName(), isSelected, isClicked);
    }

    if (isClicked && !isSelected)
    {
        m_selectedFolder = folderNode;
        m_selectedFiles.clear();
    }

    if (SketchPopup::BeginContext(folderNode->GetName()))
    {
        if (SketchMenu::Begin("Create"))
        {
            SketchPopup::MenuItemOpenPopup("Folder", "Create Folder");
            Sketch::Seperator();
            SketchPopup::MenuItemOpenPopup("Scene", "Create Scene");
            SketchPopup::MenuItemOpenPopup("Lua Script", "Create Lua Script");
            SketchPopup::MenuItemOpenPopup("Material", "Create Material");
            SketchPopup::MenuItemOpenPopup("Shader", "Create Shader");
            SketchPopup::MenuItemOpenPopup("Terrain", "Create Terrain");
            SketchPopup::MenuItemOpenPopup("Text File", "Create Text File");


            static std::string inputText = "";
            if (SketchPopup::Dialog("Create Folder", "Folder Name:", "Create", "Cancel", inputText))
            {
                std::string folderpath = folderNode->GetFullRelativePath() + inputText;
                FileSystem::CreateFolder(folderpath);
                inputText.clear();
                m_refresh = true;
            }
            else if (SketchPopup::Dialog("Create Scene", "Scene Name:", "Create", "Cancel", inputText))
            {
                std::string filepath = folderNode->GetFullRelativePath() + inputText + ".scn";
                FileSystem::CreateFile(filepath, "[]");
                inputText.clear();
                m_refresh = true;
            }
            else if (SketchPopup::Dialog("Create Lua Script", "Lua Script Name:", "Create", "Cancel", inputText))
            {
                std::string filepath = folderNode->GetFullRelativePath() + inputText + ".lua";
                FileSystem::CreateFile(filepath);
                inputText.clear();
                m_refresh = true;
            }
            else if (SketchPopup::Dialog("Create Material", "Material Name:", "Create", "Cancel", inputText))
            {
                std::string filepath = folderNode->GetFullRelativePath() + inputText + ".mt";
                FileSystem::CreateFile(filepath);
                inputText.clear();
                m_refresh = true;
            }
            else if (SketchPopup::Dialog("Create Shader", "Shader Name:", "Create", "Cancel", inputText))
            {
                std::string filepath = folderNode->GetFullRelativePath() + inputText + ".shader";
                FileSystem::CreateFile(filepath);
                inputText.clear();
                m_refresh = true;
            }
            else if (SketchPopup::Dialog("Create Terrain", "Terrain Name:", "Create", "Cancel", inputText))
            {
                std::string filepath = folderNode->GetRelativePath() + inputText + ".trn";
                Terrain* terrain = new Terrain();
                terrain->Save(filepath);
                delete terrain;
                m_refresh = true;
            }
            else if (SketchPopup::Dialog("Create Text File", "Filename:", "Create", "Cancel", inputText))
            {
                std::string filepath = folderNode->GetFullRelativePath() + inputText + ".txt";
                FileSystem::CreateFile(filepath);
                inputText.clear();
                m_refresh = true;
            }

            SketchMenu::End();
        }

        if (folderNode->GetFullRelativePath() != FileSystem::GetRelativeDataPath() &&
            folderNode->GetFullRelativePath() != FileSystem::GetRelativeEditorDataPath())
        {
       
            SketchPopup::MenuItemOpenPopup("Delete", "Delete Folder");
            SketchPopup::MenuItemOpenPopup("Rename", "Rename Folder");

            if (SketchPopup::DialogYesNo("Delete Folder", "Are you sure?\nThis will delete this folder all\nof its subfolders permanently."))
            {
                FileSystem::DeleteFolder(folderNode->GetFullRelativePath().substr(0, folderNode->GetFullRelativePath().find_last_of('/')));
                m_refresh = true;
            }
        }
        else
        {
            SketchMenu::Item("Delete", false);
            SketchMenu::Item("Rename", false);
        }

        SketchPopup::End();
    }

    if (isOpen)
    {
        for (int32 i = 0; i < folderNode->GetChildCount(); ++i)
        {
            DrawFolderNode(folderNode->GetChild(i));
        }

        SketchTree::EndNode();
    }
}

bool AssetBrowserWindow::FindSelectedFolderByName(FolderNode* folderNode, const std::string& folderpath)
{
    if (folderNode->GetFullRelativePath() == folderpath)
    {
        m_selectedFolder = folderNode;
        return true;
    }

    for (int32 i = 0; i < folderNode->GetChildCount(); ++i)
    {
        if (FindSelectedFolderByName(folderNode->GetChild(i), folderpath))
        {
            return true;
        }
    }

    return false;
}

void AssetBrowserWindow::Refresh()
{
    std::string currentFolder;
    if (m_selectedFolder)
    {
        currentFolder = m_selectedFolder->GetFullRelativePath();
        m_selectedFolder = nullptr;
    }

    if (m_editorData)
    {
        delete m_editorData;
        m_editorData = nullptr;
    }

    if (m_data)
    {
        delete m_data;
        m_data = nullptr;
    }

    m_data = new FolderNode(FileSystem::GetRelativeDataPath());
    m_editorData = new FolderNode(FileSystem::GetRelativeEditorDataPath());

    if (!currentFolder.empty() && !FindSelectedFolderByName(m_data, currentFolder))
    {
        if (!FindSelectedFolderByName(m_editorData, currentFolder))
        {
            m_selectedFiles.clear();
        }
    }
}

void AssetBrowserWindow::SetUp()
{
    Refresh();
}

void AssetBrowserWindow::TearDown()
{
}
} // namespace snack
