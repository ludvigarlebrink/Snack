#include "SceneManager.hpp"
#include "Transform.hpp"

namespace spy
{
SceneManager::SceneManager()
    : m_nextInstanceID(0u)
    , m_scene(nullptr)
{
    SetUp();
}

SceneManager::~SceneManager()
{
    TearDown();
}

void SceneManager::CollectGarbage()
{
    for (int32 i = 0; i < m_toBeDestroyed.size(); ++i)
    {
        delete m_toBeDestroyed[i];
    }

    m_toBeDestroyed.clear();
}

void SceneManager::Destroy(Transform* transform)
{
    for (int32 i = 0; i < m_toBeDestroyed.size(); ++i)
    {
        if (m_toBeDestroyed[i] == transform)
        {
            return;
        }
    }

    m_toBeDestroyed.push_back(transform);
}

void SceneManager::DestroyImmediate(Transform* transform)
{
    delete transform;
}

Transform* SceneManager::GetSceneRoot()
{
    return m_scene;
}

Transform* SceneManager::Instantiate()
{
    Transform* transform = new Transform(m_scene, m_nextInstanceID);
    ++m_nextInstanceID;
    return transform;
}

Transform* SceneManager::Instantiate(Transform* parent)
{
    if (!parent)
    {
        Transform* transform = new Transform(m_scene, m_nextInstanceID);
        ++m_nextInstanceID;
        return transform;
    }

    Transform* transform = new Transform(parent, m_nextInstanceID);
    ++m_nextInstanceID;
    return transform;
}

void SceneManager::SetUp()
{
    m_scene = new Transform(nullptr, m_nextInstanceID);
    m_scene->m_isScene = true;
    m_scene->m_name = "Scene";
    ++m_nextInstanceID;
}

void SceneManager::TearDown()
{
    if (m_scene)
    {
        delete m_scene;
    }
}
} // namespace spy
