#include "ObjParser.hpp"

#include <sstream>
#include <fstream>

namespace spy
{
ObjParser::ObjParser()
{
}

ObjParser::~ObjParser()
{
}

std::string ObjParser::GetError() const
{
    return std::string();
}

bool ObjParser::Parse(const std::string& filename, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals,
    std::vector<glm::vec2>& textureCoordiantes, std::vector<uint32>& elements)
{
    if (filename.substr(filename.size() - 4, 4) != ".obj")
    {
        return false;
    }

    std::ifstream f(filename);

    if (!f.is_open())
    {
        return false;
    }

    while (!f.eof())
    {
        std::string line;
        std::getline(f, line);
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v")
        {
            glm::vec3 position;
            ss >> position.x >> position.y >> position.z;
            positions.push_back(position);
        }
        else if (type == "vn")
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (type == "vt")
        {
            glm::vec2 textureCoordiante;
            ss >> textureCoordiante.x >> textureCoordiante.y;
            textureCoordiantes.push_back(textureCoordiante);
        }
        else if (type == "f")
        {
            int32 e0;
            int32 e1;
            int32 e2;
            ss >> e0 >> e1 >> e2;
            elements.push_back(e0);
            elements.push_back(e1);
            elements.push_back(e2);
        }
    }
}
} // namespace spy
