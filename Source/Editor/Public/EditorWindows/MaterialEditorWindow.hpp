#pragma once

#include "BaseTypes.hpp"
#include "EngineForward.hpp"
#include "EditorWindow.hpp"
#include "RenderCoreForward.hpp"
#include "EngineForward.hpp"

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

private:

    Material* m_material;
};
}// namespace spy
