#include "Rendering/GfxOutputStream.hpp"
#include "UtilsInclude.hpp"

namespace snack
{
GfxOutputStream::GfxOutputStream()
    : m_buffer(nullptr)
    , m_bufferSize(0u)
    , m_bufferCapacity(0u)
    , m_bufferIncrement(1000000u)
{
}

GfxOutputStream::~GfxOutputStream()
{
}

void GfxOutputStream::Close()
{
    if (!m_file.is_open())
    {
        return;
    }

    for (auto& h : m_headers)
    {
        h.location += sizeof(Header) * m_headers.size() + sizeof(int32);
    }

    int32 headerCount = m_headers.size();
    m_file.write(reinterpret_cast<char*>(&headerCount), sizeof(int32));
    m_file.write(reinterpret_cast<char*>(m_headers.data()), sizeof(Header) * m_headers.size());
    m_file.write(m_buffer, m_bufferSize);

    m_file.close();

    delete[] m_buffer;
    m_buffer = nullptr;
    m_bufferSize = 0;
    m_bufferCapacity = 0; 
}

bool GfxOutputStream::Open(const std::string& filename)
{
    m_file.open(filename, std::ios::in | std::ios::binary);
    if (!m_file.is_open())
    {
        return false;
    }

    m_buffer = new char[m_bufferIncrement];
    m_bufferCapacity = m_bufferIncrement;

    return true;
}
int32 GfxOutputStream::SaveStaticMesh(const std::string& name, int32 parentId, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const std::vector<StaticVertex>& vertices, const std::vector<uint32>& elements)
{
    int32 id = m_headers.size();
    Header header;
    header.id = id;
    memcpy(header.name, name.c_str(), name.size() + 1 > 128 ? 128 : name.size() + 1);
    header.location = m_bufferSize;
    header.parentId = parentId;
    header.position = position;
    header.rotation = rotation;
    header.scale = scale;
    header.type = Type::STATIC_MESH;
    m_headers.push_back(header);

    int32 vertexCount = vertices.size();
    memcpy(m_buffer + m_bufferSize, &vertexCount, sizeof(int32));
    m_bufferSize += sizeof(int32);
    memcpy(m_buffer + m_bufferSize, vertices.data(), sizeof(StaticVertex) * vertexCount);
    m_bufferSize += sizeof(StaticVertex) * vertexCount;

    int32 elementCount = elements.size();
    memcpy(m_buffer + m_bufferSize, &elementCount, sizeof(int32));
    m_bufferSize += sizeof(int32);
    memcpy(m_buffer + m_bufferSize, elements.data(), sizeof(StaticVertex) * vertices.size());
    m_bufferSize += sizeof(uint32) * elementCount;

    return id;
}
} // namespace snack
