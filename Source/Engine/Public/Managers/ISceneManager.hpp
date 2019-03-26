#pragma once

#include "BaseTypes.hpp"

namespace spy
{
class Transform;
class Engine;

class ENGINE_API ISceneManager
{
    friend Engine;

public:

    virtual ~ISceneManager() = default;

    virtual void CollectGarbage() = 0;

    virtual void Destroy(Transform* pTransform) = 0;

    virtual void DestroyImmediate(Transform* transform) = 0;

    virtual Transform* GetSceneRoot() = 0;

    virtual Transform* Instantiate() = 0;

    virtual Transform* Instantiate(Transform* parent) = 0;
};
} // namespace spy