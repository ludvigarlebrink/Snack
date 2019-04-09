#pragma once

#include "BaseTypes.hpp"
#include "EditorWindow.hpp"
#include "RenderCoreForward.hpp"

namespace snack
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

    Texture* m_texture;
    Framebuffer* m_framebuffer;
};
} // namespace snack
