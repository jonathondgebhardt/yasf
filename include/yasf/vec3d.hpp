#pragma once

#include <array>
#include <cmath>
#include <numeric>
#include <ostream>

#include "yasf/math.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class YASF_EXPORT Vec3d
{
public:
    constexpr Vec3d() = default;

    explicit constexpr Vec3d(double scalar)  // NOLINT
        : Vec3d{{scalar, scalar, scalar}}
    {
    }

    constexpr Vec3d(double x, double y, double z)  // NOLINT
        : Vec3d{{x, y, z}}
    {
    }

    explicit constexpr Vec3d(std::array<double, 3> data)
        : m_data{data}
    {
    }

    constexpr auto operator==(const Vec3d&) const -> bool = default;
    constexpr auto operator!=(const Vec3d&) const -> bool = default;

    constexpr auto operator==(std::array<double, 3> data) const -> bool
    {
        return yasf::math::double_eq(m_data[0], data[0])
            && yasf::math::double_eq(m_data[1], data[1])
            && yasf::math::double_eq(m_data[1], data[1]);
    }

    constexpr auto operator!=(std::array<double, 3> data) const -> bool
    {
        return yasf::math::double_ne(m_data[0], data[0])
            && yasf::math::double_ne(m_data[1], data[1])
            && yasf::math::double_ne(m_data[1], data[1]);
    }

    constexpr auto x() const -> double { return m_data[0]; }

    constexpr auto x() -> double& { return m_data[0]; }

    constexpr auto y() const -> double { return m_data[1]; }

    constexpr auto y() -> double& { return m_data[1]; }

    constexpr auto z() const -> double { return m_data[2]; }

    constexpr auto z() -> double& { return m_data[2]; }

    constexpr auto operator+(const Vec3d& vec) const -> Vec3d
    {
        const auto data = std::array{m_data[0] + vec.m_data[0],
                                     m_data[1] + vec.m_data[1],
                                     m_data[2] + vec.m_data[2]};
        return Vec3d{data};
    }

    constexpr auto operator+(double scalar) const -> Vec3d
    {
        auto tmp = Vec3d{m_data};
        tmp.m_data[0] += scalar;
        tmp.m_data[1] += scalar;
        tmp.m_data[2] += scalar;
        return tmp;
    }

    constexpr auto operator+=(const Vec3d& vec) -> Vec3d&
    {
        auto tmp = Vec3d{m_data};
        tmp = tmp + vec;
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto operator+=(double scalar) -> Vec3d&
    {
        auto tmp = Vec3d{m_data};
        tmp = tmp + scalar;
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto operator-(const Vec3d& vec) const -> Vec3d
    {
        const auto data = std::array{m_data[0] - vec.m_data[0],
                                     m_data[1] - vec.m_data[1],
                                     m_data[2] - vec.m_data[2]};
        return Vec3d{data};
    }

    constexpr auto operator-(double scalar) const -> Vec3d
    {
        auto tmp = Vec3d{m_data};
        tmp.m_data[0] -= scalar;
        tmp.m_data[1] -= scalar;
        tmp.m_data[2] -= scalar;
        return tmp;
    }

    constexpr auto operator-=(const Vec3d& vec) -> Vec3d&
    {
        auto tmp = Vec3d{m_data};
        tmp = tmp - vec;
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto operator-=(double scalar) -> Vec3d&
    {
        auto tmp = Vec3d{m_data};
        tmp = tmp - scalar;
        m_data = tmp.m_data;
        return *this;
    }

    // TODO: consider adding time overload
    constexpr auto operator*(double factor) const -> Vec3d
    {
        auto tmp = Vec3d{m_data};
        tmp.m_data[0] *= factor;
        tmp.m_data[1] *= factor;
        tmp.m_data[2] *= factor;
        return tmp;
    }

    constexpr auto operator*=(double factor) -> Vec3d&
    {
        auto tmp = Vec3d{m_data};
        tmp = tmp * factor;
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto operator/(double factor) const -> Vec3d
    {
        auto tmp = Vec3d{m_data};
        tmp.m_data[0] /= factor;
        tmp.m_data[1] /= factor;
        tmp.m_data[2] /= factor;
        return tmp;
    }

    constexpr auto operator/=(double factor) -> Vec3d&
    {
        auto tmp = Vec3d{m_data};
        tmp = tmp / factor;
        m_data = tmp.m_data;
        return *this;
    }

    auto mag() const -> double
    {
        const auto sum_of_products = std::accumulate(  // NOLINT
            m_data.begin(),
            m_data.end(),
            0.0,
            [](const auto acc, const auto component)
            { return acc + (component * component); });
        return std::sqrt(sum_of_products);
    }

    auto normal() const -> Vec3d
    {
        auto tmp = Vec3d{m_data};
        tmp /= tmp.mag();
        return tmp;
    }

    auto normalize() -> Vec3d&
    {
        const auto tmp = Vec3d{m_data}.normal();
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto zero() -> void { m_data = {}; }

    constexpr auto is_zero() const -> bool
    {
        return yasf::math::double_eq(m_data[0], 0.0)
            && yasf::math::double_eq(m_data[1], 0.0)
            && yasf::math::double_eq(m_data[2], 0.0);
    }

    friend auto operator<<(std::ostream& stream,
                           const Vec3d& vec) -> std::ostream&
    {
        stream << '{' << vec.x() << "}, {" << vec.y() << "}, {" << vec.z()
               << '}';
        return stream;
    }

private:
    YASF_SUPPRESS_C4251
    std::array<double, 3> m_data{};
};

}  // namespace yasf
