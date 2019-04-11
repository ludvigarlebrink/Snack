#include "RenderWindow.hpp"
#include "RenderError.hpp"
#include "glad/glad.h"

namespace snack
{
RenderWindow::RenderWindow()
    : m_window(nullptr)
{
}

RenderWindow::RenderWindow(const std::string& title, int32 width, int32 height)
    : m_window(nullptr)
{
    Create(title, width, height);
}

RenderWindow::~RenderWindow()
{
    if (m_context)
    {
        SDL_GL_DeleteContext(m_context);
    }

    if (m_window)
    {
        SDL_DestroyWindow(m_window);
    }
}

void RenderWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderWindow::ClearColorBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderWindow::ClearDepthBuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

bool RenderWindow::Create(const std::string& title, int32 width, int32 height)
{
    // @todo hack remove some, init somewhere else.
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_windowWidth = width;
    m_windowHeight = height;

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_window)
    {
        return false;
    }

    m_context = SDL_GL_CreateContext(m_window);
    if (!m_context)
    {
        return false;
    }

    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        return false;
    }

    glViewport(0, 0, width, height);
    m_viewportX = 0;
    m_viewportY = 0;
    m_viewportWidth = width;
    m_viewportHeight = height;

    // @todo hack!
    glLineWidth(3.0f);

    return true;
}

void RenderWindow::EnableBlend(bool enable)
{
    enable ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    SPY_CHECK_RENDER_ERROR();
}

void RenderWindow::EnableCullFace(bool enable)
{
    enable ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    SPY_CHECK_RENDER_ERROR();
}

void RenderWindow::EnableDepthTest(bool enable)
{
    enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    SPY_CHECK_RENDER_ERROR();
}

void RenderWindow::EnableScissorTest(bool enable)
{
    enable ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
    SPY_CHECK_RENDER_ERROR();
}

SDL_GLContext RenderWindow::GetContextHandle() const
{
    return m_context;
}

int32 RenderWindow::GetViewportHeight() const
{
    return m_viewportHeight;
}

int32 RenderWindow::GetViewportWidth() const
{
    return m_viewportWidth;
}

int32 RenderWindow::GetViewportX() const
{
    return m_viewportX;
}

int32 RenderWindow::GetViewportY() const
{
    return m_viewportY;
}

SDL_Window* RenderWindow::GetWindowHandle() const
{
    return m_window;
}

int32 RenderWindow::GetWindowHeight() const
{
    return m_windowHeight;
}

int32 RenderWindow::GetWindowWidth() const
{
    return m_windowWidth;
}

void RenderWindow::MakeCurrent()
{
    SDL_GL_MakeCurrent(m_window, m_context);
}

void RenderWindow::SetBlendFunction(BlendFactor sourceFactor, BlendFactor destinationFactor)
{
    glBlendFunc(ToGLBlendFactor(sourceFactor), ToGLBlendFactor(destinationFactor));
    SPY_CHECK_RENDER_ERROR();
}

void RenderWindow::SetClearColor(const glm::vec4& clearColor)
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    SPY_CHECK_RENDER_ERROR();
}

void RenderWindow::SetViewport(int32 x, int32 y, int32 width, int32 height)
{
    m_viewportX = x;
    m_viewportY = y;
    m_viewportWidth = width;
    m_viewportHeight = height;
    glViewport(x, y, width, height);
    SPY_CHECK_RENDER_ERROR();
}

void RenderWindow::Scissor(int32 x, int32 y, int32 width, int32 height)
{
    glScissor(x, y, width, height);
    SPY_CHECK_RENDER_ERROR();
}

void RenderWindow::Present()
{
    SDL_GL_SwapWindow(m_window);
    SPY_CHECK_RENDER_ERROR();
}

uint32 RenderWindow::ToGLBlendFactor(BlendFactor blendFactor)
{
    switch (blendFactor)
    {
    case BlendFactor::CONSTANT_ALPHA:
        return GL_CONSTANT_ALPHA;
    case BlendFactor::DESTINATION_COLOR:
        return GL_DST_COLOR;
    case BlendFactor::ONE:
        return GL_ONE;
    case BlendFactor::ONE_MINUS_SOURCE_ALPHA:
        return GL_ONE_MINUS_SRC_ALPHA;
    case BlendFactor::ONE_MINUS_DESTINATION_COLOR:
        return GL_ONE_MINUS_DST_COLOR;
    case BlendFactor::SOURCE_ALPHA:
        return GL_SRC_ALPHA;
    case BlendFactor::SOURCE_COLOR:
        return GL_SRC_COLOR;
    case BlendFactor::ZERO:
        return GL_ZERO;
    default:
        break;
    }

    return GL_ONE;
}
} // namespace snack
