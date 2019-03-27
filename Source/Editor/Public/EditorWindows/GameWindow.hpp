#pragma once

#include "BaseTypes.hpp"
#include "EditorWindow.hpp"
#include "RenderCoreForward.hpp"

namespace spy
{
class EDITOR_API GameWindow final : public EditorWindow
{
public:

    GameWindow();

    ~GameWindow();

    std::string GetTitle() override;

protected:

    void OnDraw(f32 deltaTime) override;

private:

    void SetUp();

    void TearDown();

private:

    int32 m_height;
    int32 m_width;

    Texture* m_texture;
    Framebuffer* m_framebuffer;
};
} // namespace spy