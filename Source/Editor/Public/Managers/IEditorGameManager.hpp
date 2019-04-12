#pragma once

#include "BaseTypes.hpp"
#include "EngineForward.hpp"
#include "GameState.hpp"

namespace snack
{
class Editor;

class IEditorGameManager
{
    friend Editor;

public:

    virtual ~IEditorGameManager() = default;

    virtual GameState GetGameState() = 0;

    virtual void Play() = 0;

    virtual void Pause() = 0;

    virtual void Stop() = 0;

protected:

    virtual void Tick(f32 deltaTime) = 0;
};
} // namespace snack
