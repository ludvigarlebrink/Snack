#include "Variables\BaseVariable.hpp"

namespace spy
{
BaseVariable::~BaseVariable()
{
}

std::string spy::BaseVariable::GetKey() const
{
    return m_key;
}

void BaseVariable::SetKey(const std::string& key)
{
    m_key = key;
}
} // namespace spy
