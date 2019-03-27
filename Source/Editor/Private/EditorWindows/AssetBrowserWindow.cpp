#include "EditorWindows/AssetBrowserWindow.hpp"
#include "PlatformInclude.hpp"
#include "SketchInclude.hpp"

#include <iostream>

namespace spy
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

        if (Sketch::Button("Refersh"))
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
            SketchPopup::MenuItemOpenPopup("Text File", "Create Text File");

            static std::string inputText = "";
            if (SketchPopup::Dialog("Create Folder", "Folder Name:", "Create", "Cancel", inputText))
            {
                std::string folderpath = folderNode->GetRelativePath() + inputText;
                FileSystem::CreateFolder(folderpath);
                inputText.clear();
                m_refresh = true;
            }
            else if (SketchPopup::Dialog("Create Scene", "Scene Name:", "Create", "Cancel", inputText))
            {
                std::string filepath = folderNode->GetRelativePath() + inputText + ".scene";
                FileSystem::CreateFile(filepath);
                inputText.clear();
                m_refresh = true;
            }
            else if (SketchPopup::Dialog("Create Lua Script", "Lua Script Name:", "Create", "Cancel", inputText))
            {
                std::string filepath = folderNode->GetRelativePath() + inputText + ".lua";
                FileSystem::CreateFile(filepath);
                inputText.clear();
                m_refresh = true;
            }
            else if (SketchPopup::Dialog("Create Text File", "File Name:", "Create", "Cancel", inputText))
            {
                std::string filepath = folderNode->GetRelativePath() + inputText + ".txt";
                FileSystem::CreateFile(filepath);
                inputText.clear();
                m_refresh = true;
            }

            SketchMenu::End();
        }

        if (folderNode->GetRelativePath() != FileSystem::GetRelativeDataPath() &&
            folderNode->GetRelativePath() != FileSystem::GetRelativeEditorDataPath())
        {
            SketchPopup::MenuItemOpenPopup("Rename", "Rename Folder");


            SketchPopup::MenuItemOpenPopup("Delete", "Delete Folder");
            if (SketchPopup::DialogYesNo("Delete Folder", "Are you sure?\nThis will delete this folder all\nof its subfolders permanently."))
            {
                FileSystem::DeleteFolder(folderNode->GetRelativePath().substr(0, folderNode->GetRelativePath().find_last_of('/')));
                m_refresh = true;
            }
        }
        else
        {
            SketchMenu::Item("Rename", false);
            SketchMenu::Item("Delete", false);
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
    if (folderNode->GetRelativePath() == folderpath)
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
        currentFolder = m_selectedFolder->GetRelativePath();
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
} // namespace spy