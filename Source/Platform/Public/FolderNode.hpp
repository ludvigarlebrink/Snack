#pragma once

#include "BaseTypes.hpp"

#include <vector>
#include <string>

namespace snack
{
class PLATFORM_API FolderNode final
{
public:

    struct FileInfo
    {
        /**
         * @brief Name of file.
         */
        std::string name;

        /**
         * @brief Relative path from were the search began.
         */
        std::string relativePath;

        /**
         * @brief Full relative path from executable.
         */
        std::string fullRelativePath;

        /**
         * @brief Extension of file.
         */
        std::string extension;
    };

public:

    FolderNode(const std::string& folderpath);

    FolderNode(const std::string& folderpath, int32 offset, FolderNode* parent);

    ~FolderNode();

    FolderNode* GetChild(int32 index) const;

    int32 GetChildCount() const;

    FileInfo GetFileInfo(int32 index) const;

    int32 GetFileInfoCount() const;

    std::string GetFullRelativePath() const;

    std::string GetName() const;

    std::string GetRelativePath() const;

    bool IsLeaf() const;

private:

    void SetUp(const std::string& folderpath, int32 offset, FolderNode* parent);

private:

    std::string m_name;
    std::string m_relativePath;
    std::string m_fullRelativePath;

    FolderNode* m_parent;

    std::vector<FolderNode*> m_children;
    std::vector<FileInfo> m_fileInfos;
};
} // namespace
