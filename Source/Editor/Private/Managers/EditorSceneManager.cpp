#include "EditorSceneManager.hpp"
#include "EngineInclude.hpp"

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
