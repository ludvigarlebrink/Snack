#pragma once

#include "BaseTypes.hpp"

#include <typeinfo>
#include <string>

namespace snack
{
class Engine;
class IAssetManager;
class ISceneManager;
class Transform;

class ENGINE_API BaseComponent
{
    friend Engine;

public:

    BaseComponent(Transform* pEntity);

    virtual ~BaseComponent();

    virtual std::string GetComponentID() = 0;

    /**
     * @brief Get the transform this component is attached to.
     * @return Transform this component is attached to.
     */
    Transform* GetTransform() const;

    bool IsEnabled() const;

    virtual void OnEditorGizmo();

    virtual void OnEditorInspector();

    void SetEnabled(bool enabled);

private:

    bool m_isEnabled;
    Transform* m_pTransform;
};
} // namespace snack
