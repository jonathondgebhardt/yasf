#include <memory>

#include "yasf/entity.hpp"

#include "yasf/entity_factory.hpp"
#include "yasf/position.hpp"
#include "yasf/status.hpp"
#include "yasf/uuid.hpp"

namespace yasf
{

auto entity_factory::build() -> std::unique_ptr<entity>
{
    auto builder = entity_factory{};
    return builder.build_impl();
}

auto entity_factory::build_impl() -> std::unique_ptr<entity>
{
    // TODO: do i have to repeat myself? do i want to somehow reuse the object
    // factory?
    auto obj = std::make_unique<entity>();
    obj->add_component(std::make_unique<status>());
    obj->add_component(std::make_unique<uuid>());
    obj->add_component(std::make_unique<position>());
    return obj;
}

}  // namespace yasf
