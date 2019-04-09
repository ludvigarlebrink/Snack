#include "Rendering/GfxInputStream.hpp"

#include <fstream>

namespace snack
{
GfxInputStream::GfxInputStream()
{
}

GfxInputStream::~GfxInputStream()
{
}

void GfxInputStream::Close()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

bool GfxInputStream::LoadStaticMesh(const std::string& name, std::vector<StaticVertex>& vertices, std::vector<uint32>& elements)
{
    if (!m_file.is_open())
    {
        return false;
    }

    for (auto& header : m_headers)
    {
        if (name == std::string(header.name))
        {
            if (header.type != Type::STATIC_MESH)
            {
                return false;
            }

            LoadStaticMesh(header.location, vertices, elements);
            return true;
        }
    }

    return false;
}

bool GfxInputStream::Open(const std::string& filename)
{
    m_file.open(filename, std::ios::in | std::ios::binary);
    if (!m_file.is_open())
    {
        m_file.close();
        return false;
    }

    int32 headerCount = 0;
    m_file.read(reinterpret_cast<char*>(&headerCount), sizeof(int32));

    m_headers.resize(headerCount);
    m_file.read(reinterpret_cast<char*>(m_headers.data()), sizeof(Header) * headerCount);

    return true;
}

void GfxInputStream::LoadSkinnedMesh(uint64 location, std::vector<SkinnedVertex>& vertices, std::vector<uint32>& elements)
{
    m_file.seekg(location);

    int32 vertexCount;
    m_file.read(reinterpret_cast<char*>(&vertexCount), sizeof(int32));
    vertices.resize(vertexCount);
    m_file.read(reinterpret_cast<char*>(vertices.data()), sizeof(SkinnedVertex) * vertexCount);

    int32 elementCount;
    m_file.read(reinterpret_cast<char*>(&elementCount), sizeof(int32));
    elements.resize(elementCount);
    m_file.read(reinterpret_cast<char*>(elements.data()), sizeof(uint32) * elementCount);
}

void GfxInputStream::LoadStaticMesh(uint64 location, std::vector<StaticVertex>& vertices, std::vector<uint32>& elements)
{
    m_file.seekg(location);

    int32 vertexCount;
    m_file.read(reinterpret_cast<char*>(&vertexCount), sizeof(int32));
    vertices.resize(vertexCount);
    m_file.read(reinterpret_cast<char*>(vertices.data()), sizeof(StaticVertex) * vertexCount);

    int32 elementCount;
    m_file.read(reinterpret_cast<char*>(&elementCount), sizeof(int32));
    elements.resize(elementCount);
    m_file.read(reinterpret_cast<char*>(elements.data()), sizeof(uint32) * elementCount);
}
} // namespace snack
