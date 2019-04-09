#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace snack
{
class EditorWindowManager;

class EDITOR_API EditorWindow
{
    friend EditorWindowManager;

public:
    
    EditorWindow();

    virtual ~EditorWindow();

    virtual std::string GetTitle() = 0;

protected:

    virtual void OnDraw(f32 deltaTime);
};
} // namespace snack
