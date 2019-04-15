#pragma once

#include "Managers/IEditorGameManager.hpp"

namespace snack
{
class EditorGameManager final : public IEditorGameManager
{
public:

    EditorGameManager();

    ~EditorGameManager();

    GameState GetGameState() override;

    void Play() override;

    void Pause() override;

    void Stop() override;

protected:

    void Tick(f32 deltaTime) override;

private:

    GameState m_gameState;
};
} // namespace snack
