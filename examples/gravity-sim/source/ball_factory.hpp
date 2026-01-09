#pragma once

#include <memory>

#include "yasf/entity.hpp"
#include "yasf/entity_factory.hpp"

inline auto build_ball(float radius = 10.0f) -> std::unique_ptr<yasf::Entity>
{
    auto ball = yasf::EntityFactory::build();
    ball->set_meta_data("radius", radius);
    return ball;
}
