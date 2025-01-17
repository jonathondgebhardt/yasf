#include <sstream>
#include <string_view>

#include "yasf/uuid.hpp"

#include <boost/uuid/uuid_generators.hpp>  // NOLINT
#include <boost/uuid/uuid_io.hpp>

#include "yasf/component.hpp"

namespace yasf
{

uuid::uuid()
    : component("uuid")
{
    auto const boost_uuid = boost::uuids::random_generator()();
    std::stringstream stream;
    stream << boost_uuid;
    m_uuid = stream.str();
}

auto uuid::get() const -> std::string_view
{
    return m_uuid;
}

}  // namespace yasf
