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

    void Load(cereal::JSONInputArchive& archive) override;

#ifdef SPY_EDITOR
    void OnEditorInspector() override;
#endif

    void Save(cereal::JSONOutputArchive& archive) override;
};
} // namespace snack
