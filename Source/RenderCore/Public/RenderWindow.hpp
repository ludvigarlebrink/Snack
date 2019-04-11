#pragma once

#include "BaseTypes.hpp"

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include <string>

namespace snack
{
/**
 * @brief A window used for rendering.
 */
class RENDER_CORE_API RenderWindow
{
public:

    enum class BlendFactor : uint32
    {
        CONSTANT_ALPHA,
        DESTINATION_COLOR,
        ONE,
        ONE_MINUS_SOURCE_ALPHA,
        ONE_MINUS_DESTINATION_COLOR,
        SOURCE_ALPHA,
        SOURCE_COLOR,
        ZERO
    };

public:

    /**
     * @brief Creates a render window.
     */
    RenderWindow();

    /**
     * @brief Creates a render window.
     *
     * @param title Title of this window.
     * @param width Width of this window.
     * @param height Height of this window.
     */
    RenderWindow(const std::string& title, int32 width, int32 height);

    /**
     * @brief Destroys a render window.
     */
    virtual ~RenderWindow();

    /**
     * @brief Clears the backbuffer.
     */
    void Clear();

    /**
     * @brief Clears color buffer only.
     */
    void ClearColorBuffer();

    /**
     * @bríef Clear depth buffer only. 
     */
    void ClearDepthBuffer();

    /**
     * @brief Creates a window.
     *
     * @param title Title of this window.
     * @param width Width of this window.
     * @param height Height of this window.
     * @return True if successfully created. False if not.
     */
    bool Create(const std::string& title, int32 width, int32 height);

    void EnableBlend(bool enable);

    void EnableCullFace(bool enable);

    void EnableDepthTest(bool enable);

    void EnableScissorTest(bool enable);

    SDL_GLContext GetContextHandle() const;

    int32 GetViewportHeight() const;

    int32 GetViewportWidth() const;

    int32 GetViewportX() const;

    int32 GetViewportY() const;

    SDL_Window* GetWindowHandle() const;

    int32 GetWindowHeight() const;

    int32 GetWindowWidth() const;

    void MakeCurrent();

    void SetBlendFunction(BlendFactor sourceFactor, BlendFactor destinationFactor);

    /**
     * @brief Set the color the backbuffer will be cleared with.
     *
     * @param clearColor Color the backbuffer will be cleared with.
     */
    void SetClearColor(const glm::vec4& clearColor);

    void SetViewport(int32 x, int32 y, int32 width, int32 height);

    void Scissor(int32 x, int32 y, int32 width, int32 height);

    /**
     * @brief Swap the front with the backbuffer.
     */
    void Present();

private:

    static uint32 ToGLBlendFactor(BlendFactor blendFactor);

private:

    SDL_Window* m_window;
    SDL_GLContext m_context;

    int32 m_viewportX;
    int32 m_viewportY;
    int32 m_viewportWidth;
    int32 m_viewportHeight;
    int32 m_windowWidth;
    int32 m_windowHeight;
};
} // namespace snack

/**
 * @class snack::RenderWindow
 * @ingroup RenderCore
 *
 * @code
 * // Create a window.
 * Window win();
 *
 * // Create the window with error handling.
 * if (win.create() == false)
 * {
 *     // Window was not successfully create.
 *     return false;
 * }
 * @endcode
 */
