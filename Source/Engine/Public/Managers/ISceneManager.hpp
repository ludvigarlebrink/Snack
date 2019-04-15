#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace snack
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

    virtual std::string GetFilename() const = 0;

    virtual Transform* GetSceneRoot() = 0;

    virtual Transform* Instantiate() = 0;

    virtual Transform* Instantiate(Transform* parent) = 0;

    virtual Transform* InstantiateFromPrototype(Transform* prototype) = 0;

    virtual bool Load(const std::string& filename) = 0;

    virtual bool Save(const std::string& filename) = 0;
};
} // namespace snack
