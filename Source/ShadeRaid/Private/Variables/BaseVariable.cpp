#include "Variables\BaseVariable.hpp"

namespace snack
{
BaseVariable::~BaseVariable()
{
}

std::string snack::BaseVariable::GetKey() const
{
    return m_key;
}

void BaseVariable::SetKey(const std::string& key)
{
    m_key = key;
}
} // namespace snack
