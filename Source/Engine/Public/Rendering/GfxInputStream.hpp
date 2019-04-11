#pragma once

#include "IGfxStream.hpp"

#include <fstream>
#include <vector>

namespace snack
{
/**
 * @brief Graphic output stream.
 */
class GfxInputStream final : public IGfxStream
{
public:

    GfxInputStream();

    ~GfxInputStream();

    void Close() override;

    bool LoadStaticMesh(const std::string& name, std::vector<StaticVertex>& vertices, std::vector<uint32>& elements);

    bool Open(const std::string& filename) override;

private:

    void LoadSkinnedMesh(uint64 location, std::vector<SkinnedVertex>& vertices, std::vector<uint32>& elements);

    void LoadStaticMesh(uint64 location, std::vector<StaticVertex>& vertices, std::vector<uint32>& elements);

private:

    std::ifstream m_file;
    std::vector<Header> m_headers;
};
} // namespace snack
