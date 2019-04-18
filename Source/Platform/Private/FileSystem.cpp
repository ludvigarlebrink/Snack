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

void FileSystem::GetFilesByExtension(const std::string& folderpath, const std::string& extension, std::vector<std::string>& filepaths, bool recursive)
{
    for (const auto& entry : std::filesystem::directory_iterator(folderpath))
    {
        if (entry.is_regular_file())
        {
            std::string ext = entry.path().generic_u8string();
            ext = ext.substr(ext.find_last_of("."));
            if (ext == extension)
            {
                filepaths.push_back(entry.path().generic_u8string());
            }
        }
        else if (entry.is_directory() && recursive)
        {
            GetFilesByExtension(entry.path().generic_u8string(), extension, filepaths, true);
        }
    }
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
