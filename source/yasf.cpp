#include <string>
#include <format>

#include "yasf/yasf.hpp"

exported_class::exported_class()
    : m_name {std::format("{}", "yasf")}
{
}

auto exported_class::name() const -> char const*
{
  return m_name.c_str();
}
