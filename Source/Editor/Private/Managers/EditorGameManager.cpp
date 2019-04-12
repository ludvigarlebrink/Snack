#include "EditorGameManager.hpp"

namespace snack
{
EditorGameManager::EditorGameManager()
    : m_gameState(GameState::NONE)
{
}

EditorGameManager::~EditorGameManager()
{
}

GameState EditorGameManager::GetGameState()
{
    return m_gameState;
}

void EditorGameManager::Play()
{
    
}

void EditorGameManager::Pause()
{
}

void EditorGameManager::Stop()
{
}

void EditorGameManager::Tick(f32 deltaTime)
{
}
} // namespace snack
