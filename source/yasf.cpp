#include <format>
#include <string_view>

#include "yasf/yasf.hpp"

exported_class::exported_class()
    : m_name {std::format("{}", "yasf")}
{
}

auto exported_class::name() const -> std::string_view
{
  return m_name;
}
