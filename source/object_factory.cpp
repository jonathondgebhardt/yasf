#include <memory>

#include "yasf/object.hpp"

#include "yasf/object_factory.hpp"
#include "yasf/status.hpp"
#include "yasf/uuid.hpp"

namespace yasf
{

auto object_factory::build() -> std::unique_ptr<object>
{
    auto obj = std::make_unique<object>();
    obj->add_component(std::make_unique<status>());
    obj->add_component(std::make_unique<uuid>());
    return obj;
}

}  // namespace yasf
