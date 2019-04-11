#pragma once

#include <string>

namespace snack
{
class PLATFORM_API FileSystem
{
public:

    static bool CreateFile(const std::string& filename);

    static bool CreateFolder(const std::string& folderpath);

    static bool DeleteFolder(const std::string& folderpath);

    static std::string GetRelativeDataPath();

    static std::string GetRelativeDataPath(const std::string& filename);

    static std::string GetRelativeEditorDataPath();

    static std::string GetRelativeEditorDataPath(const std::string& filename);
};
} // namespace snack
