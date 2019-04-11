#pragma once

#include "EditorWindow.hpp"
#include "PlatformForward.hpp"

#include <string>
#include <vector>

namespace snack
{
class EDITOR_API AssetBrowserWindow final : public EditorWindow
{
public:

    AssetBrowserWindow();

    ~AssetBrowserWindow();

    std::string GetTitle() override;

protected:

    void OnDraw(f32 deltaTime) override;

private:

    void DrawFolderNode(FolderNode* folderNode);

    bool FindSelectedFolderByName(FolderNode* folderNode, const std::string& folderpath);

    void Refresh();

    void SetUp();

    void TearDown();

private:

    bool m_refresh;

    std::string m_search;
    FolderNode* m_selectedFolder;
    FolderNode* m_data;
    FolderNode* m_editorData;

    std::vector<int32> m_selectedFiles;
};
} // namespace snack
