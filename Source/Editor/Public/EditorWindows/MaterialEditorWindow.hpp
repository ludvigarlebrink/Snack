#pragma once

#include "BaseTypes.hpp"
#include "EngineForward.hpp"
#include "EditorWindow.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RenderCoreForward.hpp"
#include <vector>

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

    void SetColor(const std::vector<glm::vec4>& colors, const glm::vec4 color);

private:

    Material* m_material;

    glm::vec4 m_color;

    std::vector<glm::vec4> m_colors;

    bool m_IsMaterial;
};
}// namespace spy
