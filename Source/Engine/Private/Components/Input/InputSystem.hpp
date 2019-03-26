#pragma once

#include "BaseTypes.hpp"
#include "Input/Button.hpp"
#include "Input/Key.hpp"

namespace spy
{
class InputSystem final
{
public:

    InputSystem();

    ~InputSystem();

    void Tick();

private:

    void SetUp();

    void TearDown();
};
} // namespace spy
