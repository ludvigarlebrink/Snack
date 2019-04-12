#pragma once

#include "BaseTypes.hpp"
#include "EngineForward.hpp"

namespace snack
{
class IEditorSceneManager
{
public:

    virtual ~IEditorSceneManager() = default;

    virtual void ClearSelectedTransforms() = 0;

    virtual void CopySelectedTransforms() = 0;

    virtual void CopyTransform(Transform* transform) = 0;

    virtual void DeleteSelectedTransforms() = 0;

    virtual void DuplicateSelectedTransforms() = 0;

    virtual Transform* GetSelectedTransform(int32 index) = 0;

    virtual int32 GetSelectedTransformCount() = 0;

    virtual void PasteTransforms() = 0;

    virtual void PasteTransforms(Transform* parent) = 0;

    virtual void PushSelectedTransfrom(Transform* transform) = 0;

    virtual void RemoveSelectedTransfrom(int32 index) = 0;
};
} // namespace snack
