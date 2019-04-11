#pragma once

#include "Managers/IEditorSceneManager.hpp"

#include <vector>

namespace snack
{
class EditorSceneManager final : public IEditorSceneManager
{
public:

    EditorSceneManager();

    ~EditorSceneManager();

    void ClearSelectedTransforms() override;

    Transform* GetSelectedTransform(int32 index) override;

    virtual int32 GetSelectedTransformCount() override;

    void PushSelectedTransfrom(Transform* transform) override;

    void RemoveSelectedTransfrom(int32 index) override;

private:

    void SetUp();

    void TearDown();

private:

    std::vector<Transform*> m_selectedTransforms;
};
} // namespace snack
