/**
 * Parameters.h
 * Contains all the parameters used in the algorithm
 */
#include <cstdint>

// Number of ants
// In paper called 'm'
// Paper has default value: m=n
// num_ants is only used if num_ants_equals_num_cities is false
const uint32_t num_ants = 10;
const bool num_ants_equals_num_cities = true;

// Initial pheremone value
// In paper called 'c' or tau_0
// Paper has default value: 1
const double initial_pheromone = 1;

// alpha, the influence of pheromones
// Paper has as default 1
const double alpha = 1;

// beta, the influence of distance
// Paper has as default 2
const double beta = 2;

// rho, the evaporation rate
// Paper has as default 0.5
const double rho = 0.5;

// Quantity of pheromone laid
// Paper has as default 100
const double Q = 100;

