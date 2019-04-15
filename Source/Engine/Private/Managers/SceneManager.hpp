#pragma once

#include "Managers/ISceneManager.hpp"
#include "InstanceID.hpp"

#include <vector>

namespace snack
{
class SceneManager final : public ISceneManager
{
public:

    SceneManager();

    ~SceneManager();

    void CollectGarbage() override;

    void Destroy(Transform* transform) override;

    void DestroyImmediate(Transform* transform) override;

    std::string GetFilename() const override;

    Transform* GetSceneRoot() override;

    Transform* Instantiate() override;

    Transform* Instantiate(Transform* parent) override;

    Transform* InstantiateFromPrototype(Transform* prototype) override;

    bool Load(const std::string& filename) override;

    bool Save(const std::string& filename) override;

private:

    void InstantiateFromPrototypeChildren(Transform* parent, Transform* prototype);

    void SetUp();

    void TearDown();

private:

    InstanceID m_nextInstanceID;
    Transform* m_scene;

    std::vector<Transform*> m_toBeDestroyed;
    std::string m_filename;
};
} // namespace snack
