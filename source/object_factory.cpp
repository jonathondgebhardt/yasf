#include <memory>

#include "yasf/object.hpp"

#include "yasf/object_factory.hpp"

namespace yasf
{

auto ObjectFactory::build() -> std::unique_ptr<Object>
{
    auto obj = std::make_unique<Object>();
    return obj;
}

}  // namespace yasf
