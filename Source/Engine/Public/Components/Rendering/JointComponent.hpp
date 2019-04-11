#pragma once

#include "Components/BaseComponent.hpp"
#include "Mesh.hpp"

#include <glm/glm.hpp>

namespace snack
{
class JointComponent final : public BaseComponent
{
public:

    JointComponent(Transform* transform);

    ~JointComponent();

    std::string GetComponentID() override;

    void OnEditorInspector() override;
};
} // namespace snack
