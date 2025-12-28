#pragma once

#include <stdexcept>

#include "yasf/logger.hpp"

namespace yasf
{

class Ensure
{
public:
    Ensure(bool condition, const std::string& failure_message)
    {
        if (!condition) {
            yasf::log::critical(failure_message);
            throw std::runtime_error(failure_message);
        }
    }
};

}  // namespace yasf
