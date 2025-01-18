#pragma once

#include "yasf/clock.hpp"
#include "yasf/object.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class YASF_EXPORT mover
{
public:
    auto set_root(object* root) -> void;

    auto process() -> void;

private:
    object* m_root{};

    // TODO: don't have this as a member
    clock m_clock{1.0};
};

}  // namespace yasf
