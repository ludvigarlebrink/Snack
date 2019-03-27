#pragma once

#include "BaseTypes.hpp"
#include "RenderCoreForward.hpp"

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include <vector>

namespace spy
{
class SketchGizmo;

class SKETCH_API SketchInternal
{
    friend SketchGizmo;

private:

    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
    };

    struct GizmoDrawData
    {
        std::vector<Vertex> vertices;
        std::vector<Vertex> verticesOverdrawn;
        std::vector<Vertex> lines;
        std::vector<Vertex> linesOverdrawn;
        std::vector<uint32> elements;
        std::vector<uint32> elementsOverdrawn;
        std::vector<uint32> lineElements;
        std::vector<uint32> lineElementsOverdrawn;
    };

public:

    static void NewFrame(RenderWindow* renderWindow);

    static void Render(RenderWindow* renderWindow);

    static void RenderGizmos(RenderWindow* renderWindow, const glm::mat4& viewProjection);

    static void ProcessEvent(SDL_Event* event);

    static void SetUp(RenderWindow* renderWindow);

    static void TearDown();

private:

    static void ApplyStyle();

    static void SetUpGizmos();

private:

    static Mesh* m_mesh;
    static Shader* m_shader;
    static Texture* m_fontTexture;

    static Mesh* m_gizmoMesh;
    static Shader* m_gizmoShader;
    static GizmoDrawData m_gizmoDrawData;
};
} // namespace spy
