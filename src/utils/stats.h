/**
 * Stats.h
 * Stats module to keep track and log statistics and other important data
 * This class also makes the result logs
 */
#include <cstdint>
#include <vector>

using namespace std;

class Stats{
    public:
        Stats(): iterations({}) {};
    private:
        vector<uint32_t> iterations;
};