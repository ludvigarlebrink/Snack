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

    void CopySelectedTransforms() override;

    void CopyTransform(Transform* transform) override;

    void DeleteSelectedTransforms() override;

    void DuplicateSelectedTransforms() override;

    Transform* GetSelectedTransform(int32 index) override;

    int32 GetSelectedTransformCount() override;

    void PasteTransforms() override;

    void PasteTransforms(Transform* parent) override;

    void PushSelectedTransfrom(Transform* transform) override;

    void RemoveSelectedTransfrom(int32 index) override;

private:

    void SetUp();

    void TearDown();

private:

    std::vector<Transform*> m_selectedTransforms;
    std::vector<Transform*> m_toBePasted;
};
} // namespace snack
