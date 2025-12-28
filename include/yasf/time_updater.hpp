#pragma once

#include "yasf/component.hpp"
#include "yasf/types.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class YASF_EXPORT TimeUpdater : public Component
{
public:
    virtual auto next_time() -> time_microseconds = 0;

protected:
    explicit TimeUpdater(std::string name)
        : Component(std::move(name))
    {
    }

private:
    YASF_SUPPRESS_C4251
};

}  // namespace yasf
