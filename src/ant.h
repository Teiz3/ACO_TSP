// Very much still WIP

#include <vector>
#include <cstdint>
#include <assert.h>

class Ant{
    public:
        std::vector<uint32_t> visited;

        void visitNode(uint32_t node);

        Ant(double a, double b) : _alpha(a), _beta(b) {};
    private:
        double _alpha;
        double _beta;
};