#include "FileSystem.hpp"

#include <filesystem>
#include <fstream>

namespace snack
{
bool FileSystem::CreateFile(const std::string& filepath)
{
    std::ofstream f(filepath);
    if (f.is_open())
    {
        f.close();
        return true;
    }

    return false;
}

bool FileSystem::CreateFile(const std::string& filepath, const std::string& data)
{
    std::ofstream f(filepath);
    if (f.is_open())
    {
        f << data;
        f.close();
        return true;
    }

    return false;
}

bool FileSystem::CreateFolder(const std::string & folderpath)
{
    return std::filesystem::create_directory(folderpath);
}

bool FileSystem::DeleteFile(const std::string& filepath)
{
    return std::filesystem::remove(filepath);
}

bool FileSystem::DeleteFolder(const std::string& folderpath)
{
    return std::filesystem::remove_all(folderpath);
}

std::string FileSystem::GetRelativeDataPath()
{
    return "Data/";
}

std::string FileSystem::GetRelativeDataPath(const std::string& filepath)
{
    return "Data/" + filepath;
}

std::string FileSystem::GetRelativeEditorDataPath()
{
    return "EditorData/";
}

std::string FileSystem::GetRelativeEditorDataPath(const std::string& filepath)
{
    return "EditorData/" + filepath;
}
} // namespace snack
