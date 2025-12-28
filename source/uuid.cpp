#include <sstream>

#include "yasf/uuid.hpp"

#include <boost/uuid/uuid_generators.hpp>  // NOLINT
#include <boost/uuid/uuid_io.hpp>

namespace yasf
{

Uuid::Uuid()
    : m_uuid(boost::uuids::random_generator()())
{
    std::stringstream stream;
    stream << m_uuid;
    m_uuid_str = stream.str();
}

auto Uuid::operator==(const Uuid& other) const -> bool
{
    return m_uuid == other.m_uuid;
}

}  // namespace yasf
