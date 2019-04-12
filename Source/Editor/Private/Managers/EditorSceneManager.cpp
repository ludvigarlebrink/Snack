#include "EditorSceneManager.hpp"
#include "EngineInclude.hpp"

#include <algorithm>

namespace snack
{
EditorSceneManager::EditorSceneManager()
{
}

EditorSceneManager::~EditorSceneManager()
{
}

void EditorSceneManager::ClearSelectedTransforms()
{
    m_selectedTransforms.clear();
}

void EditorSceneManager::DeleteSelectedTransforms()
{
    if (m_selectedTransforms.empty())
    {
        return;
    }

    std::vector<Transform*> toBeDestroyed;
    for (auto selected : m_selectedTransforms)
    {
        toBeDestroyed.push_back(selected);
    }
    m_selectedTransforms.clear();

    // Destroy objects with higher depths first.
    auto sortFunc = [](Transform* lhs, Transform* rhs)->bool
    {
        return lhs->GetDepth() > rhs->GetDepth();
    };

    std::sort(toBeDestroyed.begin(), toBeDestroyed.end(), sortFunc);
    for (auto t : toBeDestroyed)
    {
        Manager::Scene()->DestroyImmediate(t);
    }
}

Transform* EditorSceneManager::GetSelectedTransform(int32 index)
{
    return m_selectedTransforms[index];
}

int32 EditorSceneManager::GetSelectedTransformCount()
{
    return m_selectedTransforms.size();
}

void EditorSceneManager::PushSelectedTransfrom(Transform* transform)
{
    m_selectedTransforms.push_back(transform);
}

void EditorSceneManager::RemoveSelectedTransfrom(int32 index)
{
    m_selectedTransforms.erase(m_selectedTransforms.begin() + index);
}

void EditorSceneManager::SetUp()
{
}

void EditorSceneManager::TearDown()
{
}
} // namespace snack
