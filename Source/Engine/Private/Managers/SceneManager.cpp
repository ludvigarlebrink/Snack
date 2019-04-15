#include "SceneManager.hpp"
#include "Transform.hpp"
#include "PlatformInclude.hpp"

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <fstream>
#include <sstream>

namespace snack
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

std::string SceneManager::GetFilename() const
{
    return m_filename;
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

Transform* SceneManager::InstantiateFromPrototype(Transform* prototype)
{
    Transform* transform = new Transform(prototype->GetParent(), m_nextInstanceID);
    ++m_nextInstanceID;
    for (auto p : prototype->m_children)
    {
        Transform* child = new Transform(transform, m_nextInstanceID);
        ++m_nextInstanceID;
        InstantiateFromPrototypeChildren(child, p);
    }
    return transform;
}

bool SceneManager::Load(const std::string& filename)
{
    std::ifstream f(FileSystem::GetRelativeDataPath(filename));
    if (!f.is_open())
    {
        return false;
    }

    delete m_scene;

    m_scene = new Transform(nullptr, m_nextInstanceID);
    m_scene->m_isScene = true;
    m_scene->m_name = "Scene";
    ++m_nextInstanceID;

    std::stringstream ss;
    {
        std::string source((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        ss << source;
    }

    cereal::JSONInputArchive archive(ss);
    m_scene->Load(archive);

    m_filename = filename;

    return true;
}

bool SceneManager::Save(const std::string& filename)
{
    std::stringstream ss;

    {
        cereal::JSONOutputArchive archive(ss);
        archive.makeArray();
        m_scene->Save(archive);
    }

    std::ofstream f(FileSystem::GetRelativeDataPath(filename));
    if (!f.is_open())
    {
        return false;
    }

    f << ss.str();

    f.close();

    m_filename = filename;

    return true;
}

void SceneManager::InstantiateFromPrototypeChildren(Transform* parent, Transform* prototype)
{
    for (auto p : prototype->m_children)
    {
        Transform* child = new Transform(parent, m_nextInstanceID);
        ++m_nextInstanceID;
        InstantiateFromPrototypeChildren(child, p);
    }
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
} // namespace snack
