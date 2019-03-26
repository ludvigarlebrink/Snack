#pragma once

#include "Managers/ISceneManager.hpp"
#include "InstanceID.hpp"

#include <vector>

namespace spy
{
class SceneManager final : public ISceneManager
{
public:

    SceneManager();

    ~SceneManager();

    void CollectGarbage() override;

    void Destroy(Transform* transform) override;

    void DestroyImmediate(Transform* transform) override;

    Transform* GetSceneRoot() override;

    Transform* Instantiate() override;

    Transform* Instantiate(Transform* parent) override;

private:

    void SetUp();

    void TearDown();

private:

    InstanceID m_nextInstanceID;
    Transform* m_scene;

    std::vector<Transform*> m_toBeDestroyed;
};
} // namespace spy
