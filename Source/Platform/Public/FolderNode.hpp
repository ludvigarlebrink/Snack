#pragma once

#include "BaseTypes.hpp"

#include <vector>
#include <string>

namespace spy
{
class PLATFORM_API FolderNode final
{
public:

    struct FileInfo
    {
        std::string name;
        std::string relativePath;
        std::string extension;
    };

public:

    FolderNode(const std::string& folderpath);

    FolderNode(const std::string& folderpath, FolderNode* parent);

    ~FolderNode();

    FolderNode* GetChild(int32 index) const;

    int32 GetChildCount() const;

    FileInfo GetFileInfo(int32 index) const;

    int32 GetFileInfoCount() const;

    std::string GetName() const;

    std::string GetRelativePath() const;

    bool IsLeaf() const;

private:

    void SetUp(const std::string& folderpath, FolderNode* parent);

private:

    std::string m_name;
    std::string m_relativePath;

    FolderNode* m_parent;

    std::vector<FolderNode*> m_children;
    std::vector<FileInfo> m_fileInfos;
};
} // namespace
