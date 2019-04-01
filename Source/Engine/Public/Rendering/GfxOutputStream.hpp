#pragma once

#include "IGfxStream.hpp"

#include <fstream>
#include <vector>

namespace spy
{
/**
 * @brief Graphic output stream.
 */
class GfxOutputStream final : public IGfxStream
{
public:

    GfxOutputStream();

    ~GfxOutputStream();

    void Close() override;

    bool Open(const std::string& filename) override;

private:

    std::ofstream m_file;
    std::vector<Header> m_headers;
};
} // namespace spy
