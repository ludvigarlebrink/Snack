#include "EditorWindows/SceneGraphWindow.hpp"
#include "EditorManager.hpp"
#include "EngineInclude.hpp"
#include "SketchInclude.hpp"

#include <algorithm>
#include <iostream>

namespace spy
{
SceneGraphWindow::SceneGraphWindow()
    : m_dragDropReparented(false)
    , m_dragDropSource(nullptr)
    , m_dragDropTarget(nullptr)
{
}

SceneGraphWindow::~SceneGraphWindow()
{
}

std::string SceneGraphWindow::GetTitle()
{
    return "Scene Graph";
}

void SceneGraphWindow::OnDraw(f32 deltaTime)
{
    if (m_dragDropReparented)
    {
        bool sourceIsParentOfTarget = false;
        Transform* parent = m_dragDropTarget->GetParent();
        while (!parent->IsScene() && !sourceIsParentOfTarget)
        {
            sourceIsParentOfTarget = parent == m_dragDropSource;
            parent = parent->GetParent();
        }

        if (!sourceIsParentOfTarget)
        {
            m_dragDropSource->SetParent(m_dragDropTarget);
        }

        m_dragDropReparented = false;
    }

    Transform* scene = Manager::Scene()->GetSceneRoot();
    DrawTransform(scene);
}

bool SceneGraphWindow::DrawTransform(Transform* transform)
{
    bool isOpen = false;
    bool isSelected = false;
    bool isClicked = false;
    int32 selectedIndex = -1;
    for (int32 i = 0; i < EditorManager::Scene()->GetSelectedTransformCount(); ++i)
    {
        if (EditorManager::Scene()->GetSelectedTransform(i) == transform)
        {
            isSelected = true;
            selectedIndex = i;
            break;
        }
    }

    if (transform->IsLeaf())
    {
        isOpen = SketchTree::LeafNode(transform->GetName(), transform->GetInstanceID(), isSelected, isClicked);
    }
    else
    {
        isOpen = SketchTree::BeginNode(transform->GetName(), transform->GetInstanceID(), isSelected, isClicked);
    }

    if (!transform->IsScene())
    {
        if (SketchDragDrop::BeginSource(transform->GetName()))
        {
            SketchDragDrop::SetPayload("Transfrom", &transform);
            SketchDragDrop::EndSource();
        }
    }

    if (SketchDragDrop::BeginTarget())
    {
        SketchDragDrop::Payload payload;
        if (SketchDragDrop::AcceptPayload("Transfrom", payload))
        {
            void** data = static_cast<void**>(payload.data);
            m_dragDropSource = static_cast<Transform*>(*data);
            m_dragDropTarget = transform;
            m_dragDropReparented = true;
        }
        SketchDragDrop::EndTarget();
    }

    if (isClicked)
    {
        if (SketchEvent::ModRepeat(Mod::SHIFT))
        {
            if (!isSelected)
            {
                EditorManager::Scene()->PushSelectedTransfrom(transform);
            }
            else
            {
                EditorManager::Scene()->RemoveSelectedTransfrom(selectedIndex);
            }
        }
        else if (!isSelected || EditorManager::Scene()->GetSelectedTransformCount() > 1)
        {
            EditorManager::Scene()->ClearSelectedTransforms();
            EditorManager::Scene()->PushSelectedTransfrom(transform);
        }
    }

    if (SketchPopup::BeginContext(transform->GetInstanceID()))
    {
        if (SketchMenu::Item("Copy", !transform->IsScene()))
        {

        }

        if (SketchMenu::Item("Paste"))
        {

        }

        Sketch::Seperator();

        if (SketchMenu::Item("Rename"))
        {

        }

        if (SketchMenu::Item("Duplicate", !transform->IsScene()))
        {

        }

        if (SketchMenu::Item("Delete", !transform->IsScene()))
        {
            if (EditorManager::Scene()->GetSelectedTransformCount() == 1)
            {
                if (FindSelectedTransformInChildren(transform, EditorManager::Scene()->GetSelectedTransform(0)))
                {
                    EditorManager::Scene()->ClearSelectedTransforms();
                }
            }
            else if (EditorManager::Scene()->GetSelectedTransformCount() > 1)
            {
                std::vector<Transform*> toBeDestroyed;
                for (int32 i = 0; i < EditorManager::Scene()->GetSelectedTransformCount(); ++i)
                {
                    toBeDestroyed.push_back(EditorManager::Scene()->GetSelectedTransform(i));
                }
                EditorManager::Scene()->ClearSelectedTransforms();

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
            else
            {
                Manager::Scene()->DestroyImmediate(transform);
            }

            SketchPopup::End();
            if (isOpen)
            {
                SketchTree::EndNode();
            }
            return false;
        }

        Sketch::Seperator();

        if (SketchMenu::Item("Create Transform"))
        {
            Manager::Scene()->Instantiate(transform);
        }

        SketchPopup::End();
    }

    if (isOpen)
    {
        for (int32 i = 0; i < transform->GetChildCount(); ++i)
        {
            if (!DrawTransform(transform->GetChild(i)))
            {
                SketchTree::EndNode();
                return false;
            }
        }

        SketchTree::EndNode();
    }

    return true;
}
bool SceneGraphWindow::FindSelectedTransformInChildren(Transform* transform, Transform* selectedTransfrom)
{
    if (transform == selectedTransfrom)
    {
        return true;
    }

    for (int32 i = 0; i < transform->GetChildCount(); ++i)
    {
        if (FindSelectedTransformInChildren(transform->GetChild(i), selectedTransfrom));
        {
            return true;
        }
    }

    return false;
}
} // namespace spy
