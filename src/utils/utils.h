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
using json = nlohmann::json;

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
#ifdef _WIN32
    localtime_s(&tm, &t);   // Windows
#else
    localtime_r(&t, &tm);   // POSIX
#endif
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

template <class Rep, class Period>
double to_seconds(std::chrono::duration<Rep, Period> d)
{
    return std::chrono::duration<double>(d).count();
}

inline double round_to(double value, double precision = 1.0)
{
    return std::round(value / precision) * precision;
}

class Terminator {
    public: 
        Terminator(uint32_t maxIter) : maxIter(maxIter) {};
        virtual bool canContinue(double pathLen) = 0;
        inline void resetTerminator(){ bestPath = 1e300; i = 0; };
        virtual json to_json() = 0;
        const char* name;
        virtual ~Terminator() {};
    protected:
        double bestPath = 1e300;
        uint32_t i = 0;
        uint32_t maxIter;
};

class MaxTerminator : public Terminator{
    public:
        MaxTerminator(uint32_t maxIter) : Terminator(maxIter) {
            name = "Max iteration terminator";
        };

        inline virtual bool canContinue(double pathLen){
            bestPath = pathLen;
            return i++ < maxIter;
        }

        inline virtual json to_json(){
            return json{
                {"name", name},
                {"maxIter", maxIter}
            };
        }
};

class NoChangeTerminator : public Terminator{
    public:
        NoChangeTerminator(uint32_t noChangeCount, uint32_t maxIter) : 
            noChangeCount(noChangeCount), Terminator(maxIter) {
            name = "No change terminator";

            };

        inline virtual bool canContinue(double pathLen){
            if (pathLen < bestPath){
                bestPath = pathLen;
                nrOfChanges = 0;
            }else{
                nrOfChanges++;
            }
            return (nrOfChanges < noChangeCount) && (i++ < maxIter);
        }

        inline virtual json to_json(){
            return json{
                {"name", name},
                {"maxIter", maxIter},
                {"noChangeCount", noChangeCount}
            };
        }

    private:
        uint32_t noChangeCount;
        uint32_t maxIter;
        uint32_t nrOfChanges = 0;
};

class SmallChangeTerminator : public Terminator{
    /*
    In this new algorithm, the termination condition is that the length
    difference for the optimal paths of neighboring iterations is less than
    10−5. In addition, to avoid infinite iteration, the maximum number
    of iterations N is given.
    */
    public:
        SmallChangeTerminator(uint32_t maxIter) : Terminator(maxIter){
            name = "Small change terminator";
        };

        inline virtual bool canContinue(double pathLen){
            double diff = std::abs(bestPath - pathLen);
            bestPath = pathLen;
            return (diff > changeThreshold) && (i++ < maxIter);
        }

        inline virtual json to_json(){
            return json{
                {"name", name},
                {"maxIter", maxIter},
                {"changeThreshold", changeThreshold}
            };
        }
    private:
        double changeThreshold = 10e-5;
};