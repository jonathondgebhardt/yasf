#pragma once

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
};

}  // namespace yasf
