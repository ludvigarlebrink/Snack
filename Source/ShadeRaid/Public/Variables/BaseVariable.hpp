#pragma once

#include "BaseTypes.hpp"

#include <string>

namespace snack
{
class BaseVariable
{
public:

    virtual ~BaseVariable();

    std::string GetKey() const;

    void SetKey(const std::string& key);

private:

    std::string m_key;
};
} // namespace snack
