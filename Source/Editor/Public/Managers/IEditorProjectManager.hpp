#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace snack
{
class IEditorProjectManager
{
public:

    ~IEditorProjectManager() = default;

    virtual bool Load(const std::string& filepath) = 0;
};
} // namespace snack
