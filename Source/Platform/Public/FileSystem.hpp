#pragma once

#include <string>

namespace snack
{
/**
 * @brief Filesystem.
 */
class PLATFORM_API FileSystem
{
public:

    /**
     * @brief Create an empty file.
     * @param filepath Name and path of the file.
     * @return True if file has been successfully created, false if not.
     */
    static bool CreateFile(const std::string& filepath);

    /**
     * @brief Create a file with text.
     * @param filepath Name and path of the file.
     * @param data Text to add to file.
     * @return True if file has been successfully created, false if not.
     */
    static bool CreateFile(const std::string& filepath, const std::string& data);

    /**
     * @brief Creates a folder.
     * @param folderpath Path to folder.
     * @return True if folder has been successfully created, false if not.
     */
    static bool CreateFolder(const std::string& folderpath);

    static bool DeleteFolder(const std::string& folderpath);

    static std::string GetRelativeDataPath();

    static std::string GetRelativeDataPath(const std::string& filepath);

    static std::string GetRelativeEditorDataPath();

    static std::string GetRelativeEditorDataPath(const std::string& filepath);
};
} // namespace snack
