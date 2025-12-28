#include <memory>

#include "yasf/entity.hpp"

#include "yasf/entity_factory.hpp"
#include "yasf/position.hpp"
#include "yasf/velocity.hpp"

namespace yasf
{

auto EntityFactory::build() -> std::unique_ptr<Entity>
{
    // TODO: do i have to repeat myself? do i want to somehow reuse the object
    // factory?
    auto ent = std::make_unique<Entity>();
    ent->add_component(std::make_unique<Position>());
    ent->add_component(std::make_unique<Velocity>());
    return ent;
}

}  // namespace yasf
