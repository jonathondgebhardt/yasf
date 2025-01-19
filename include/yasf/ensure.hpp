#pragma once

#include <stdexcept>

namespace yasf
{

class ensure
{
public:
    ensure(bool condition, const std::string& failure_message)
    {
        if (!condition) {
            throw std::runtime_error(failure_message);
        }
    }
};

}  // namespace yasf
