#include "FileSystem.hpp"

#include <filesystem>
#include <fstream>

namespace snack
{
bool FileSystem::CreateFile(const std::string& filename)
{
    std::ofstream f(filename);
    if (f.is_open())
    {
        f.close();
        return true;
    }

    return false;
}

bool FileSystem::CreateFolder(const std::string & folderpath)
{
    return std::filesystem::create_directory(folderpath);
}

bool FileSystem::DeleteFolder(const std::string& folderpath)
{
    return std::filesystem::remove_all(folderpath);
}

std::string FileSystem::GetRelativeDataPath()
{
    return "Data/";
}

std::string FileSystem::GetRelativeDataPath(const std::string& filename)
{
    return "Data/" + filename;
}

std::string FileSystem::GetRelativeEditorDataPath()
{
    return "EditorData/";
}

std::string FileSystem::GetRelativeEditorDataPath(const std::string& filename)
{
    return "EditorData/" + filename;
}
} // namespace snack
