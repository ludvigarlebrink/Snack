#include "Components/Rendering/SkyComponent.hpp"

namespace snack
{
SkyComponent::SkyComponent(Transform* transform)
    : BaseComponent(transform)
{
}

SkyComponent::~SkyComponent()
{
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
