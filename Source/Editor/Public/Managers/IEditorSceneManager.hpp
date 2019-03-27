#pragma once

#include "BaseTypes.hpp"
#include "EngineForward.hpp"

namespace spy
{
class IEditorSceneManager
{
public:

    virtual ~IEditorSceneManager() = default;

    virtual void ClearSelectedTransforms() = 0;

    virtual Transform* GetSelectedTransform(int32 index) = 0;

    virtual int32 GetSelectedTransformCount() = 0;

    virtual void PushSelectedTransfrom(Transform* transform) = 0;

    virtual void RemoveSelectedTransfrom(int32 index) = 0;
};
} // namespace spy