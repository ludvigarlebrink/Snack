#pragma once

#include "IGfxStream.hpp"

#include <fstream>
#include <vector>

namespace snack
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

    /**
     * @return Id, -1 if something went wrong.
     */
    int32 SaveStaticMesh(const std::string& name, int32 parentId, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const std::vector<StaticVertex>& vertices, const std::vector<uint32>& elements);

private:

    std::ofstream m_file;
    std::vector<Header> m_headers;

    char* m_buffer;
    uint64 m_bufferSize;
    uint64 m_bufferCapacity;
    uint64 m_bufferIncrement;
};
} // namespace snack
