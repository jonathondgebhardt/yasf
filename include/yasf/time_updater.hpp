#pragma once

#include "yasf/component.hpp"
#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class time_updater : public component
{
public:
    virtual auto next_time() -> time_usec = 0;

protected:
    explicit time_updater(std::string name)
        : component(std::move(name))
    {
    }

private:
    YASF_SUPPRESS_C4251
};

}  // namespace yasf
