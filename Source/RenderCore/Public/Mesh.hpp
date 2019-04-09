#pragma once

#include "BaseTypes.hpp"

namespace snack
{
/**
 * @brief A vertex array.
 */
class RENDER_CORE_API Mesh
{
public:

    enum class Mode
    {
        LINE_LOOP,
        LINE_STRIP,
        LINE_STRIP_ADJACENCY,
        LINES,
        LINES_ADJACENCY,
        PATCHES,
        POINTS,
        TRIANGLE_FAN,
        TRIANGLE_STRIP,
        TRIANGLE_STRIP_ADJACENCY,
        TRIANGLES,
        TRIANGLES_ADJACENCY
    };

    /**
     * @brief Mode for which a vertex array will be optimized for.
     */
    enum class Optimization
    {
        DYNAMIC_DRAW,
        STATIC_DRAW,
        STREAM_DRAW
    };

    enum class Type
    {
        F32,
        INT32,
        VEC2,
        VEC2I,
        VEC2U,
        VEC3,
        VEC3I,
        VEC3U,
        VEC4,
        VEC4I,
        VEC4U,

        /**
         * @brief Vector 4 with unsigned bytes.
         */
        VEC4UB
    };

public:

    /**
     * @brief Creates a vertex array.
     */
    Mesh();

    /**
     * @brief Destroys a vertex array.
     */
    virtual ~Mesh();

    /**
     * @brief Bind this vertex array.
     */
    void Bind();

    /**
     * @brief Enables an attribute.
     *
     * @param index Index of attribute to enable.
     */
    void EnableAttribute(int32 index);

    /**
     * @brief Maps the array buffer for reading.
     *
     * @return Void pointer to array buffer.
     *
     * Call unmap once done reading.
     */
    void* MapForReading();

    /**
     * @brief Maps the array buffer for reading.
     *
     * @return Void pointer to array buffer.
     *
     * Call unmap once done writing.
     *
     * Mapping a buffer can be useful for things such as batch rendering. Let's look at how
     * we can do that, by creating a very simple batch renderer. First we need to have a
     * a defintion for our sprite.
     *
     * @code
     * // For instance we can define a sprite vertex.
     * struct SpriteVertex
     * {
     *     // Position of the sprite.
     *     Vector2f sprite;
     *     // The sprite's texture coordinates in UV-space.
     *     Vector2f textureCoords;
     * }
     * @endcode
     *
     * Next let's look at the code during this update function.
     *
     * @code
     * SpriteVertex* pSpriteVertices = static_cast<SpriteVertex*>(mesh.mapForWriting());
     *
     * // Lets say we have a sprite class.
     * for (auto sprite : sprites)
     * {
     *     // This will move the pointer by sizeof(SpriteVertex).
     *     ++pSriteVerteices;
     * }
     *
     * // Once we are done mapping we have to use the unmap function.
     * 
     * @endcode
     *
     * And there we have it! A simple batch renderer.
     */
    void* MapForWriting();

    template <typename T>
    T* MapForWriting();

    /**
     * @brief Render this vertex array.
     */
    void Render(Mode mode);

    /**
     * @brief Render this vertex array.
     *
     * @param count Number of vertices to render.
     */
    void Render(Mode mode, int32 count);

    void Render(Mode mode, int32 count, void* offset);

    /**
     * @brief Reserve data.
     *
     */
    void Reserve(int32 vertexCount, int32 vertexSize, int32 elementCount);

    void Reserve(int32 vertexCount, int32 vertexSize, int32 elementCount, Optimization optimization);

    /**
     * @brief Set a pointer to an attribute in the vertex array.
     *
     * @param index
     * @param type
     * @param offset
     */
    void SetAttribPtr(int32 index, Type type, int32 offset);

    /**
     * @brief This class will load (or copy) data from the ram to the v-ram.
     *
     * @param vertexData
     * @param vertexSize
     * @param vertexCount
     * @param elementData
     * @param elementCount
     */
    void SetData(void* vertexData, int32 vertexCount, int32 vertexSize, uint32* elementData, int32 elementCount);

    void SetData(void* vertexData, int32 vertexCount, int32 vertexSize, uint32* elementData, int32 elementCount, Optimization optimization);

    void SetVertexSubData(void* vertexData, int32 count, int32 offset);

    void SetElementSubData(uint32* elementData, int32 count, int32 offset);

    /**
     * @brief Unmaps the buffer.
     *
     * Call this function when done reading or writing to the buffer.
     */
    void Unmap();

private:

    uint32 ToGLMode(Mode mode);
    
    uint32 ToGLOptimization(Optimization optimization);

private:

    uint32 m_vao;
    uint32 m_vbo;
    uint32 m_ebo;
    int32 m_vertexCount;
    int32 m_vertexSize;
    int32 m_elementCount;
};

template <typename T>
T* Mesh::MapForWriting()
{
    return reinterpret_cast<T*>(MapForWriting());
}
} // namespace snack

/**
 * @class snack::VertexArray
 * @ingroup RenderCore
 */
