#include <memory>

#include "yasf/entity.hpp"

#include "yasf/entity_factory.hpp"
#include "yasf/position.hpp"
#include "yasf/status.hpp"
#include "yasf/velocity.hpp"

namespace yasf
{

auto entity_factory::build() -> std::unique_ptr<entity>
{
    // TODO: do i have to repeat myself? do i want to somehow reuse the object
    // factory?
    auto ent = std::make_unique<entity>();
    ent->add_component(std::make_unique<status>());
    ent->add_component(std::make_unique<position>());
    ent->add_component(std::make_unique<velocity>());
    return ent;
}

}  // namespace yasf
