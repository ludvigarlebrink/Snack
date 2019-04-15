#include "Components/Rendering/SkyComponent.hpp"
#include "UtilsInclude.hpp"

namespace snack
{
SkyComponent::SkyComponent(Transform* transform)
    : BaseComponent(transform)
{
}

SkyComponent::~SkyComponent()
{
}

std::string SkyComponent::GetComponentID()
{
    return CLASS_NAME(PointLightComponent);
}

void SkyComponent::Load(cereal::JSONInputArchive& archive)
{
    BaseComponent::Load(archive);
}

void SkyComponent::Save(cereal::JSONOutputArchive& archive)
{
    BaseComponent::Save(archive);
}
} // namespace snack
