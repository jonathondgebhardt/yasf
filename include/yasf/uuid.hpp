#pragma once

#include <string_view>

#include <boost/uuid.hpp>

#include "yasf/yasf_export.hpp"

namespace yasf
{

/**
 * @brief Reports the name of the library
 */
class YASF_EXPORT uuid
{
public:
    uuid();

    auto operator==(const uuid& other) const -> bool;

    auto get() const -> std::string_view { return m_uuid_str; }

    auto empty() const -> bool { return m_uuid.is_nil(); }

private:
    YASF_SUPPRESS_C4251
    boost::uuids::uuid m_uuid;
    std::string m_uuid_str;
};

}  // namespace yasf
