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

void EditorSceneManager::CopySelectedTransforms()
{
    if (m_selectedTransforms.empty())
    {
        return;
    }

    m_toBePasted.clear();
    for (auto selected : m_selectedTransforms)
    {
        if (!selected->IsScene())
        {
            m_toBePasted.push_back(selected);
        }
    }

    auto sortFunc = [](Transform* lhs, Transform* rhs)->bool
    {
        return lhs->GetDepth() > rhs->GetDepth();
    };

    std::vector<Transform*> toBeRemoved;
    for (auto t : m_toBePasted)
    {
        bool isRemoved = false;
        Transform* current = t->GetParent();
        while (!current->IsScene() && !isRemoved)
        {
            for (auto p : m_toBePasted)
            {
                if (p == current)
                {
                    toBeRemoved.push_back(t);
                    isRemoved = true;
                    break;
                }
            }

            current = current->GetParent();
        }
    }

    for (auto t : toBeRemoved)
    {
        for (int32 i = 0; i < m_toBePasted.size(); ++i)
        {
            if (m_toBePasted[i] == t)
            {
                m_toBePasted.erase(m_toBePasted.begin() + i);
                break;
            }
        }
    }
}

void EditorSceneManager::CopyTransform(Transform* transform)
{
    m_toBePasted.clear();
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
        if (!selected->IsScene())
        {
            toBeDestroyed.push_back(selected);
        }
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

void EditorSceneManager::DuplicateSelectedTransforms()
{
    if (m_selectedTransforms.empty())
    {
        return;
    }

    m_toBePasted.clear();
    for (auto selected : m_selectedTransforms)
    {
        if (!selected->IsScene())
        {
            m_toBePasted.push_back(selected);
        }
    }

    auto sortFunc = [](Transform* lhs, Transform* rhs)->bool
    {
        return lhs->GetDepth() > rhs->GetDepth();
    };

    std::vector<Transform*> toBeRemoved;
    for (auto t : m_toBePasted)
    {
        bool isRemoved = false;
        Transform* current = t->GetParent();
        while (!current->IsScene() && !isRemoved)
        {
            for (auto p : m_toBePasted)
            {
                if (p == current)
                {
                    toBeRemoved.push_back(t);
                    isRemoved = true;
                    break;
                }
            }

            current = current->GetParent();
        }
    }

    for (auto t : toBeRemoved)
    {
        for (int32 i = 0; i < m_toBePasted.size(); ++i)
        {
            if (m_toBePasted[i] == t)
            {
                m_toBePasted.erase(m_toBePasted.begin() + i);
                break;
            }
        }
    }

    for (auto t : m_toBePasted)
    {
        Manager::Scene()->InstantiateFromPrototype(t);
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

void EditorSceneManager::PasteTransforms()
{
    for (auto t : m_toBePasted)
    {
        Manager::Scene()->InstantiateFromPrototype(t);
    }
}

void EditorSceneManager::PasteTransforms(Transform* parent)
{

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
