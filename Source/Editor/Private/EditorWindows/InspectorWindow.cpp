#include "EditorWindows/InspectorWindow.hpp"
#include "EditorManager.hpp"
#include "Manager.hpp"
#include "EngineInclude.hpp"
#include "SketchInclude.hpp"

namespace snack
{
InspectorWindow::InspectorWindow()
{
}

InspectorWindow::~InspectorWindow()
{
}

std::string InspectorWindow::GetTitle()
{
    return "Inspector";
}

void InspectorWindow::OnDraw(f32 deltaTime)
{
    int32 count = EditorManager::Scene()->GetSelectedTransformCount();
    if (count == 0)
    {
        Sketch::Text("Select a transform to edit!");
    }
    else if (count > 1)
    {
        Sketch::Text("Can only edit one transform at the time!");
    }
    else
    {
        Transform* transform = EditorManager::Scene()->GetSelectedTransform(0);
        if (transform->IsScene())
        {
            Sketch::Text("Can not edit a scene!");
        }
        else
        {
            if (Sketch::Button("Add Component"))
            {
                SketchPopup::OpenPopup("Add Component");
                m_componentInfos.clear();
                Manager::Class()->GetAllComponentInfo(m_componentInfos);
            }

            if (SketchPopup::BeginModal("Add Component", glm::vec2(400.0f, 300.0f)))
            {
                Sketch::TextField("Search", m_search);

                SketchWindow::BeginChild("Add Component List", true);
                {
                    for (auto& c : m_componentInfos)
                    {
                        if (c.constructable && !transform->HasComponent(c.id) &&
                            (m_search.empty() || m_search == c.name.substr(0, m_search.length())))
                        {
                            if (Sketch::Selectable(c.name))
                            {
                                transform->AddComponent(c.id);
                                m_search.clear();
                                SketchPopup::Close();
                                break;
                            }
                        }
                    }
                }
                SketchWindow::EndChild();

                SketchPopup::End();
            }

            bool isEnabled = transform->IsEnabled();
            if (Sketch::CollapsingHeader("Transform"))
            {
                transform->OnEditorInspector();
            }

            std::vector<BaseComponent*> components;
            transform->GetAllComponents(components);
            for (auto c : components)
            {
                if (Sketch::CollapsingHeader(Manager::Class()->GetComponentName(c->GetComponentID())))
                {
                    c->OnEditorInspector();
                }
            }
        }
    }
}
} // namespace snack
