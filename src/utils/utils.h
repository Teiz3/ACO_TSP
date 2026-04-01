/**
 * Utils.h
 * Collection of useful helper functions and data types
 */
#pragma once

#include <cmath>

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