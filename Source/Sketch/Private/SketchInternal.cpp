#include "SketchInternal.hpp"
#include "RenderCoreInclude.hpp"
#include "SketchEvent.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"

#include <iostream>

namespace snack
{
Mesh* SketchInternal::m_mesh = nullptr;
Shader* SketchInternal::m_shader = nullptr;
Texture* SketchInternal::m_fontTexture = nullptr;

Mesh* SketchInternal::m_gizmoMesh = nullptr;
Shader* SketchInternal::m_gizmoShader = nullptr;
SketchInternal::GizmoDrawData SketchInternal::m_gizmoDrawData;

void SketchInternal::NewFrame(RenderWindow* renderWindow)
{
    ImGui_ImplSDL2_NewFrame(renderWindow->GetWindowHandle());
    ImGui::NewFrame();
}

void SketchInternal::Render(RenderWindow* renderWindow)
{
    // Render imgui.
    ImGui::Render();
    renderWindow->MakeCurrent();
    ImDrawData* drawData = ImGui::GetDrawData();

    int32 fbWidth = static_cast<int32>(drawData->DisplaySize.x * drawData->FramebufferScale.x);
    int32 fbHeight = static_cast<int32>(drawData->DisplaySize.y * drawData->FramebufferScale.y);

    // Avoid rendering if minimized.
    if (fbWidth <= 0 || fbHeight <= 0)
    {
        return;
    }

    renderWindow->EnableBlend(true);
    renderWindow->EnableScissorTest(true);
    renderWindow->EnableCullFace(false);
    renderWindow->EnableDepthTest(false);
    renderWindow->SetBlendFunction(RenderWindow::BlendFactor::SOURCE_ALPHA, RenderWindow::BlendFactor::ONE_MINUS_SOURCE_ALPHA);
    renderWindow->SetViewport(0, 0, fbWidth, fbHeight);

    // Setup the projection matrix.
    f32 l = drawData->DisplayPos.x;
    f32 r = drawData->DisplayPos.x + drawData->DisplaySize.x;
    f32 t = drawData->DisplayPos.y;
    f32 b = drawData->DisplayPos.y + drawData->DisplaySize.y;
    const glm::mat4 orthoProjection =
    {
        { 2.0f / (r - l), 0.0f, 0.0f, 0.0f },
        { 0.0f, 2.0f / (t - b), 0.0f, 0.0f },
        { 0.0f, 0.0f, -1.0f, 0.0f },
        { (r + l) / (l - r), (t + b) / (b - t), 0.0f, 1.0f }
    };

    glm::vec2 clipOff(drawData->DisplayPos.x, drawData->DisplayPos.y);
    glm::vec2 clipScale(drawData->FramebufferScale.x, drawData->FramebufferScale.y);

    m_shader->Use();
    m_shader->SetIntSlow("Texture", 0);
    m_shader->SetMat4Slow("ProjMtx", orthoProjection);

    for (int32 i = 0; i < drawData->CmdListsCount; ++i)
    {
        const ImDrawList* cmdList = drawData->CmdLists[i];
        uint32 indexBufferOffset = 0;

        void* vertexData = static_cast<void*>(cmdList->VtxBuffer.Data);
        int32 vertexCount = static_cast<int32>(cmdList->VtxBuffer.Size);
        uint32* elementData = static_cast<uint32*>(cmdList->IdxBuffer.Data);
        int32 elementCount = static_cast<int32>(cmdList->IdxBuffer.Size);
        m_mesh->SetVertexSubData(vertexData, vertexCount, 0);
        m_mesh->SetElementSubData(elementData, elementCount, 0);

        for (int32 j = 0; j < cmdList->CmdBuffer.Size; ++j)
        {
            const ImDrawCmd* cmd = &cmdList->CmdBuffer[j];
            glm::vec4 clipRect;
            clipRect.x = (cmd->ClipRect.x - clipOff.x) * clipScale.x;
            clipRect.y = (cmd->ClipRect.y - clipOff.y) * clipScale.y;
            clipRect.z = (cmd->ClipRect.z - clipOff.x) * clipScale.x;
            clipRect.w = (cmd->ClipRect.w - clipOff.y) * clipScale.y;

            if (clipRect.x < fbWidth && clipRect.y < fbHeight && clipRect.z >= 0.0f && clipRect.w >= 0.0f)
            {
                Texture* texture = static_cast<Texture*>(cmd->TextureId);
                if (texture)
                {
                    texture->Bind(0);
                }

                renderWindow->Scissor(static_cast<int32>(clipRect.x), static_cast<int32>(fbHeight - clipRect.w),
                    static_cast<int32>(clipRect.z - clipRect.x), static_cast<int32>(clipRect.w - clipRect.y));

                m_mesh->Render(Mesh::Mode::TRIANGLES, cmd->ElemCount, (void*)indexBufferOffset);
            }

            indexBufferOffset += cmd->ElemCount * sizeof(uint32);
        }
    }

    renderWindow->EnableScissorTest(false);
    SketchEvent::UpdateEvents();
}

void SketchInternal::RenderGizmos(RenderWindow* renderWindow, const glm::mat4& viewProjection)
{
    m_gizmoShader->Use();
    renderWindow->EnableCullFace(false);
    renderWindow->EnableBlend(true);
    renderWindow->SetBlendFunction(RenderWindow::BlendFactor::SOURCE_ALPHA, RenderWindow::BlendFactor::ONE_MINUS_SOURCE_ALPHA);
    m_gizmoShader->SetMat4Slow("ViewProjection", viewProjection);

    m_gizmoMesh->SetVertexSubData(m_gizmoDrawData.vertices.data(), m_gizmoDrawData.vertices.size(), 0);
    m_gizmoMesh->SetElementSubData(m_gizmoDrawData.elements.data(), m_gizmoDrawData.elements.size(), 0);
    m_gizmoMesh->Render(Mesh::Mode::TRIANGLES, m_gizmoDrawData.elements.size());

    m_gizmoMesh->SetVertexSubData(m_gizmoDrawData.lines.data(), m_gizmoDrawData.lines.size(), 0);
    m_gizmoMesh->SetElementSubData(m_gizmoDrawData.lineElements.data(), m_gizmoDrawData.lineElements.size(), 0);
    m_gizmoMesh->Render(Mesh::Mode::LINES, m_gizmoDrawData.lineElements.size());

    // Overdrawn.
    renderWindow->ClearDepthBuffer();

    m_gizmoMesh->SetVertexSubData(m_gizmoDrawData.verticesOverdrawn.data(), m_gizmoDrawData.verticesOverdrawn.size(), 0);
    m_gizmoMesh->SetElementSubData(m_gizmoDrawData.elementsOverdrawn.data(), m_gizmoDrawData.elementsOverdrawn.size(), 0);
    m_gizmoMesh->Render(Mesh::Mode::TRIANGLES, m_gizmoDrawData.elementsOverdrawn.size());

    m_gizmoMesh->SetVertexSubData(m_gizmoDrawData.linesOverdrawn.data(), m_gizmoDrawData.linesOverdrawn.size(), 0);
    m_gizmoMesh->SetElementSubData(m_gizmoDrawData.lineElementsOverdrawn.data(), m_gizmoDrawData.lineElementsOverdrawn.size(), 0);
    m_gizmoMesh->Render(Mesh::Mode::LINES, m_gizmoDrawData.lineElementsOverdrawn.size());

    m_gizmoDrawData.vertices.clear();
    m_gizmoDrawData.verticesOverdrawn.clear();
    m_gizmoDrawData.lineElements.clear();
    m_gizmoDrawData.lines.clear();
    m_gizmoDrawData.elements.clear();
    m_gizmoDrawData.elementsOverdrawn.clear();
    m_gizmoDrawData.linesOverdrawn.clear();
    m_gizmoDrawData.lineElementsOverdrawn.clear();
}

void SketchInternal::ProcessEvent(SDL_Event* event)
{
    ImGui_ImplSDL2_ProcessEvent(event);
    SketchEvent::ProcessEvent(event);
}

void SketchInternal::SetUp(RenderWindow* renderWindow)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    
    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(renderWindow->GetWindowHandle(), renderWindow->GetContextHandle());

    io.BackendRendererName = "imgui_impl_opengl3";

    // Vertex shader source.
    static const char* vertexShader = 
        "#version 440 core\n"
        "layout (location = 0) in vec2 Position;\n"
        "layout (location = 1) in vec2 UV;\n"
        "layout (location = 2) in vec4 Color;\n"
        "uniform mat4 ProjMtx;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "    Frag_UV = UV;\n"
        "    Frag_Color = Color;\n"
        "    gl_Position = ProjMtx * vec4(Position.xy, 0, 1);\n"
        "}\n\0";

    // Fragment shader source.
    static const char* fragmentShader =
        "#version 440 core\n"
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "uniform sampler2D Texture;\n"
        "layout (location = 0) out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
        "}\n\0";

    // Setup shader.
    m_shader = new Shader();
    m_shader->LoadShaderFromString(vertexShader, Shader::Type::VERTEX_SHADER);
    m_shader->LoadShaderFromString(fragmentShader, Shader::Type::FRAGMENT_SHADER);
    m_shader->LinkProgram();

    // Setup vertex array.
    m_mesh = new Mesh();
    static const int32 reserveSize = 65536;
    m_mesh->Reserve(reserveSize, sizeof(ImDrawVert), reserveSize, Mesh::Optimization::DYNAMIC_DRAW);
    int32 offset = 0;
    m_mesh->SetAttribPtr(0, Mesh::Type::VEC2, offset);
    offset += sizeof(glm::vec2);
    m_mesh->SetAttribPtr(1, Mesh::Type::VEC2, offset);
    offset += sizeof(glm::vec2);
    m_mesh->SetAttribPtr(2, Mesh::Type::VEC4UB, offset);

    m_mesh->EnableAttribute(0);
    m_mesh->EnableAttribute(1);
    m_mesh->EnableAttribute(2);

    // Create font texture.
    {
        ImFontConfig fontConfig;
        fontConfig.OversampleH = 1;
        fontConfig.OversampleV = 1;
        fontConfig.RasterizerMultiply = 1.6f;
        fontConfig.PixelSnapH = true;
        fontConfig.MergeMode = false;
        io.Fonts->AddFontFromFileTTF("Fonts/FiraMono-Regular.ttf", 14.0f, &fontConfig);
    }

    {
        ImFontConfig fontConfig;
        fontConfig.OversampleH = 1;
        fontConfig.OversampleV = 1;
        fontConfig.RasterizerMultiply = 1.6f;
        fontConfig.PixelSnapH = true;
        fontConfig.MergeMode = false;
        io.Fonts->AddFontFromFileTTF("Fonts/FiraMono-Regular.ttf", 24.0f, &fontConfig);
    }

//    io.Fonts->Build();

    uchar* pixels = nullptr;
    int32 width = 0;
    int32 height = 0;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    m_fontTexture = new Texture();
    m_fontTexture->SetSWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_fontTexture->SetTWrapping(Texture::Wrapping::CLAMP_TO_EDGE);
    m_fontTexture->SetMagFilter(Texture::MagFilter::NEAREST);
    m_fontTexture->SetMinFilter(Texture::MinFilter::NEAREST);
    m_fontTexture->SetData(width, height, Texture::InternalFormat::RGBA, Texture::Format::RGBA, Texture::Type::UNSIGNED_BYTE, pixels);
    io.Fonts->TexID = static_cast<ImTextureID>(m_fontTexture);

    SetUpGizmos();
    ApplyStyle();
}

void SketchInternal::TearDown()
{
    delete m_mesh;
    delete m_shader;
}

void SketchInternal::ApplyStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.0f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

    colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.53f, 0.53f, 0.53f, 0.46f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.85f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.22f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 0.53f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);

    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);

    colors[ImGuiCol_CheckMark] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.47f, 0.47f, 0.91f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.55f, 0.55f, 0.62f);

    colors[ImGuiCol_Button] = ImVec4(0.50f, 0.50f, 0.50f, 0.63f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.67f, 0.68f, 0.63f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.26f, 0.26f, 0.63f);

    colors[ImGuiCol_Header] = ImVec4(0.54f, 0.54f, 0.54f, 0.58f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.64f, 0.65f, 0.65f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 0.80f);

    // Seperator.
    colors[ImGuiCol_Separator] = ImVec4(0.58f, 0.58f, 0.58f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
    
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.87f, 0.87f, 0.87f, 0.53f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);

    colors[ImGuiCol_Tab] = ImVec4(0.01f, 0.01f, 0.01f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);

    colors[ImGuiCol_DockingPreview] = ImVec4(0.38f, 0.48f, 0.60f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.68f, 0.68f, 0.68f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.77f, 0.33f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.87f, 0.55f, 0.08f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.47f, 0.60f, 0.76f, 0.47f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.58f, 0.58f, 0.58f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    style->FrameBorderSize = 1.0f;
    style->FramePadding = ImVec2(4.0f, 2.0f);
    style->ItemSpacing = ImVec2(8.0f, 2.0f);
    style->WindowBorderSize = 1.0f;
    style->TabBorderSize = 1.0f;
    style->WindowRounding = 1.0f;
    style->ChildRounding = 1.0f;
    style->FrameRounding = 1.0f;
    style->ScrollbarRounding = 1.0f;
    style->GrabRounding = 1.0f;
    style->TabRounding = 2.0f;
}

void SketchInternal::SetUpGizmos()
{
    // Vertex shader source.
    static const char* vertexShader =
        "#version 440 core\n"
        "layout (location = 0) in vec3 Position_VS_in;\n"
        "layout (location = 1) in vec4 Color_VS_in;\n"
        "uniform mat4 ViewProjection;\n"
        "out vec4 Color_FS_in;\n"
        "void main()\n"
        "{\n"
        "    Color_FS_in = Color_VS_in;\n"
        "    gl_Position = ViewProjection * vec4(Position_VS_in, 1.0);\n"
        "}\n\0";

    // Fragment shader source.
    static const char* fragmentShader =
        "#version 440 core\n"
        "layout (location = 0) out vec4 FragColor;\n"
        "in vec4 Color_FS_in;\n"
        "void main()\n"
        "{\n"
        "    FragColor = Color_FS_in;\n"
        "}\n\0";

    // Setup shader.
    m_gizmoShader = new Shader();
    m_gizmoShader->LoadShaderFromString(vertexShader, Shader::Type::VERTEX_SHADER);
    m_gizmoShader->LoadShaderFromString(fragmentShader, Shader::Type::FRAGMENT_SHADER);
    m_gizmoShader->LinkProgram();

    static const int32 reserveSize = 65536;

    // Setup vertex array.
    m_gizmoMesh = new Mesh();
    m_gizmoMesh->Reserve(reserveSize, sizeof(Vertex), reserveSize, Mesh::Optimization::DYNAMIC_DRAW);
    
    int32 offset = 0;
    m_gizmoMesh->SetAttribPtr(0, Mesh::Type::VEC3, offset);
    offset += sizeof(glm::vec3);
    m_gizmoMesh->SetAttribPtr(1, Mesh::Type::VEC4, offset);

    m_gizmoMesh->EnableAttribute(0);
    m_gizmoMesh->EnableAttribute(1);
}
} // namespace snack
