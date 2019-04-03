#include "Rendering/GfxOutputStream.hpp"

namespace spy
{
GfxOutputStream::GfxOutputStream()
{
}

GfxOutputStream::~GfxOutputStream()
{
}

void GfxOutputStream::Close()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

bool GfxOutputStream::Open(const std::string& filename)
{
    m_file.open(filename, std::ios::in | std::ios::binary);
    if (!m_file.is_open())
    {
        m_file.close();
        return false;
    }

    return true;
}
} // namespace spy
