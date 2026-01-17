#pragma once

#include <array>
#include <cmath>
#include <numeric>
#include <ostream>

#include "yasf/math.hpp"
#include "yasf/yasf_export.hpp"

namespace yasf
{

class YASF_EXPORT Vec2d
{
public:
    using VecType = std::array<double, 2>;

    constexpr Vec2d() = default;

    explicit constexpr Vec2d(double scalar)  // NOLINT
        : Vec2d{{scalar, scalar}}
    {
    }

    constexpr Vec2d(double x, double y)  // NOLINT
        : Vec2d{{x, y}}
    {
    }

    explicit constexpr Vec2d(VecType data)
        : m_data{data}
    {
    }

    constexpr auto operator==(const Vec2d&) const -> bool = default;
    constexpr auto operator!=(const Vec2d&) const -> bool = default;

    constexpr auto operator==(VecType data) const -> bool
    {
        return yasf::math::double_eq(m_data[0], data[0])
            && yasf::math::double_eq(m_data[1], data[1]);
    }

    constexpr auto operator!=(VecType data) const -> bool
    {
        return yasf::math::double_ne(m_data[0], data[0])
            && yasf::math::double_ne(m_data[1], data[1]);
    }

    constexpr auto x() const -> double { return m_data[0]; }

    constexpr auto x() -> double& { return m_data[0]; }

    constexpr auto y() const -> double { return m_data[1]; }

    constexpr auto y() -> double& { return m_data[1]; }

    constexpr auto operator+(const Vec2d& vec) const -> Vec2d
    {
        const auto data =
            std::array{m_data[0] + vec.m_data[0], m_data[1] + vec.m_data[1]};
        return Vec2d{data};
    }

    constexpr auto operator+(double scalar) const -> Vec2d
    {
        auto tmp = Vec2d{m_data};
        tmp.m_data[0] += scalar;
        tmp.m_data[1] += scalar;
        return tmp;
    }

    constexpr auto operator+=(const Vec2d& vec) -> Vec2d&
    {
        auto tmp = Vec2d{m_data};
        tmp = tmp + vec;
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto operator+=(double scalar) -> Vec2d&
    {
        auto tmp = Vec2d{m_data};
        tmp = tmp + scalar;
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto operator-(const Vec2d& vec) const -> Vec2d
    {
        const auto data =
            std::array{m_data[0] - vec.m_data[0], m_data[1] - vec.m_data[1]};
        return Vec2d{data};
    }

    constexpr auto operator-(double scalar) const -> Vec2d
    {
        auto tmp = Vec2d{m_data};
        tmp.m_data[0] -= scalar;
        tmp.m_data[1] -= scalar;
        return tmp;
    }

    constexpr auto operator-=(const Vec2d& vec) -> Vec2d&
    {
        auto tmp = Vec2d{m_data};
        tmp = tmp - vec;
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto operator-=(double scalar) -> Vec2d&
    {
        auto tmp = Vec2d{m_data};
        tmp = tmp - scalar;
        m_data = tmp.m_data;
        return *this;
    }

    // TODO: consider adding time overload
    constexpr auto operator*(double factor) const -> Vec2d
    {
        auto tmp = Vec2d{m_data};
        tmp.m_data[0] *= factor;
        tmp.m_data[1] *= factor;
        return tmp;
    }

    constexpr auto operator*=(double factor) -> Vec2d&
    {
        auto tmp = Vec2d{m_data};
        tmp = tmp * factor;
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto operator/(double factor) const -> Vec2d
    {
        auto tmp = Vec2d{m_data};
        tmp.m_data[0] /= factor;
        tmp.m_data[1] /= factor;
        return tmp;
    }

    constexpr auto operator/=(double factor) -> Vec2d&
    {
        auto tmp = Vec2d{m_data};
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

    auto normal() const -> Vec2d
    {
        auto tmp = Vec2d{m_data};
        tmp /= tmp.mag();
        return tmp;
    }

    auto normalize() -> Vec2d&
    {
        const auto tmp = Vec2d{m_data}.normal();
        m_data = tmp.m_data;
        return *this;
    }

    constexpr auto zero() -> void { m_data = {}; }

    constexpr auto is_zero() const -> bool
    {
        return yasf::math::double_eq(m_data[0], 0.0)
            && yasf::math::double_eq(m_data[1], 0.0);
    }

    friend auto operator<<(std::ostream& stream, const Vec2d& vec)
        -> std::ostream&
    {
        stream << '{' << vec.x() << "}, {" << vec.y() << '}';
        return stream;
    }

private:
    YASF_SUPPRESS_C4251 VecType m_data{};
};

}  // namespace yasf
