#include "Rendering/Terrain.hpp"
#include "RenderCoreInclude.hpp"

#include <fstream>

namespace snack
{
Terrain::Terrain()
    : m_size(8)
    , m_heightMapResolution(8)
    , m_mesh(nullptr)
{
    SetUp();
}

Terrain::~Terrain()
{
    TearDown();
}

int32 Terrain::GetSize() const
{
    return m_size;
}

bool Terrain::Load(const std::string& filename)
{
    std::ifstream f(filename, std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        return false;
    }

    f.read(reinterpret_cast<char*>(&m_size), sizeof(int32));
    f.read(reinterpret_cast<char*>(&m_heightMapResolution), sizeof(int32));
    m_heightMapPixels.resize(m_heightMapResolution * m_heightMapResolution);
    f.read(reinterpret_cast<char*>(m_heightMapPixels.data()), m_heightMapPixels.size());

    f.close();

    Refresh();

    return true;
}

void Terrain::Refresh()
{
    Vertex* vertices = new Vertex[m_size * m_size];

    for (int32 x = 0; x < m_size; ++x)
    {
        for (int32 y = 0; y < m_size; ++y)
        {
            vertices[x * m_size + y].position = glm::vec2(x, y);
        }
    }
     
    uint32* elements = new uint32[(m_size - 1) * (m_size - 1) * 6];
    int32 i = 0;
    for (int32 x = 0; x < m_size - 1; ++x)
    {
        for (int32 y = 0; y < m_size - 1; ++y)
        {
            int32 offset = x * m_size + y;

            // Triangle 1.
            elements[i] = offset;
            ++i;
            elements[i] = offset + 1;
            ++i;
            elements[i] = offset + m_size;
            ++i;

            // Triangle 2.
            elements[i] = offset + 1;
            ++i;
            elements[i] = offset + m_size + 1;
            ++i;
            elements[i] = offset + m_size;
            ++i;
        }
    }

    m_mesh = new Mesh();
    m_mesh->SetData(vertices, m_size * m_size, sizeof(Vertex), elements, (m_size - 1) * (m_size - 1) * 6);
    m_mesh->SetAttribPtr(0, Mesh::Type::VEC2, 0);
    m_mesh->EnableAttribute(0);

    // Cleanup!
    delete[] vertices;
    delete[] elements;
}

void Terrain::Render()
{
    m_mesh->Render(Mesh::Mode::TRIANGLES);
}

bool Terrain::Save(const std::string& filename)
{
    std::ofstream f(filename, std::ios::out | std::ios::binary);
    if (!f.is_open())
    {
        return false;
    }

    f.write(reinterpret_cast<char*>(&m_size), sizeof(int32));
    f.write(reinterpret_cast<char*>(&m_heightMapResolution), sizeof(int32));
    f.write(reinterpret_cast<char*>(m_heightMapPixels.data()), m_heightMapPixels.size());

    f.close();

    return true;
}

void Terrain::SetSize(int32 size)
{
    m_size = size;
}

void Terrain::SetUp()
{
    m_heightMapPixels.resize(m_heightMapResolution * m_heightMapResolution);
    memset(m_heightMapPixels.data(), 0, m_heightMapResolution * m_heightMapResolution);
    Refresh();
}

void Terrain::TearDown()
{
    delete m_mesh;
    m_mesh = nullptr;
}
} // namespace snack
