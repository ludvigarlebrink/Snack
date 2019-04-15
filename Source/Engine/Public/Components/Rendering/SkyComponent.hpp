#pragma once

#include "Components/BaseComponent.hpp"

namespace snack
{
class ENGINE_API SkyComponent final : public BaseComponent
{
public:

    SkyComponent(Transform* transform);

    ~SkyComponent();
};
} // namespace snack
