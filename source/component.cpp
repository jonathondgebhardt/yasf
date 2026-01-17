#include <utility>

#include "yasf/component.hpp"

namespace yasf
{

Component::Component()
    : Component("component")
{
}

Component::Component(std::string name)
    : m_name{std::move(name)}
{
}

}  // namespace yasf
