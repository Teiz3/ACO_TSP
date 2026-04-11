/**
 * Utils.h
 * Collection of useful helper functions and data types
 */
#pragma once

#include <cmath>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"

struct Vec2d {
    double x_;
    double y_;

    Vec2d& operator-=(const Vec2d &other) {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    friend Vec2d operator-(const Vec2d &a, const Vec2d &b) {
        return { a.x_ - b.x_, a.y_ - b.y_ };
    }

    [[nodiscard]] double length() const { return std::sqrt(x_ * x_ + y_ * y_); }

    [[nodiscard]] double length_squared() const { return x_ * x_ + y_ * y_; }
};

inline std::string to_string(std::chrono::system_clock::time_point tp)
{
    auto t = std::chrono::system_clock::to_time_t(tp);
    std::tm tm{};
    localtime_r(&t, &tm);

    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

template <class Rep, class Period>
double to_seconds(std::chrono::duration<Rep, Period> d)
{
    return std::chrono::duration<double>(d).count();
}