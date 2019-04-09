#pragma once

#include "EditorWindow.hpp"
#include "EngineForward.hpp"

namespace snack
{
class EDITOR_API SceneGraphWindow final : public EditorWindow
{
public:

    SceneGraphWindow();

    ~SceneGraphWindow();

    std::string GetTitle() override;

protected:

    void OnDraw(f32 deltaTime) override;

private:

    bool DrawTransform(Transform* transform);

    bool FindSelectedTransformInChildren(Transform* transform, Transform* selectedTransfrom);

private:

    bool m_dragDropReparented;
    Transform* m_dragDropSource;
    Transform* m_dragDropTarget;
};
} // namespace snack
