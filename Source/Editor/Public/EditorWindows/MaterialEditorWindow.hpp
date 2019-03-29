#pragma once

#include "BaseTypes.hpp"
#include "EditorWindow.hpp"
#include "RenderCoreForward.hpp"

namespace spy
{
class EDITOR_API MaterialEditorWindow final : public EditorWindow
{
public:

    MaterialEditorWindow();

    ~MaterialEditorWindow();

    std::string GetTitle() override;

protected:

    void OnDraw(f32 deltaTime) override;

private:

    void SetUp();

    void TearDown();
};
}// namespace spy
