/**
 * Parameters.h
 * Contains all the parameters used in the algorithm
 */
#pragma once
#include <cstdint>
#include "utils/json.hpp"
using json = nlohmann::json;

// Number of ants
// In paper called 'm'
// Paper has default value: m=n
// num_ants is only used if num_ants_equals_num_cities is false
const uint32_t default_num_ants = 10;
const bool default_num_ants_equals_num_cities = true;

// Initial pheremone value
// In paper called 'c' or tau_0
// Paper has default value: 1
const double default_initial_pheromone = 1;

// alpha, the influence of pheromones
// Paper has as default 1
const double default_alpha = 1;

// beta, the influence of distance
// Paper has as default 2
const double default_beta = 2;

// rho, the evaporation rate
// Paper has as default 0.5
const double default_rho = 0.5;

// Quantity of pheromone laid
// Paper has as default 100
const double default_Q = 100;

struct Config{
    const uint32_t num_ants;
    const bool num_ants_equals_num_cities;
    const double initial_pheromone;
    const double alpha;
    const double beta;
    const double rho;
    const double Q;
    // Meeting ant specific:
    const bool use_meeting_strategy = true;
    const int32_t meeting_threshold = 1;    // v 
    const double pheromone_min = 0.00001;   // tmin
    const double pheromone_max = 1e20;      // tmax
};

inline Config defaultConfig = {
    default_num_ants,
    default_num_ants_equals_num_cities,
    default_initial_pheromone,
    default_alpha,
    default_beta,
    default_rho,
    default_Q,
};

inline json to_json(const Config& c){
    return json{
        {"num_ants", c.num_ants},
        {"num_ants_equals_num_cities", c.num_ants_equals_num_cities},
        {"initial_pheromone", c.initial_pheromone},
        {"alpha", c.alpha},
        {"beta", c.beta},
        {"rho", c.rho},
        {"Q", c.Q},
        {"use_meeting_strategy", c.use_meeting_strategy},
        {"meeting_threshold", c.meeting_threshold},
        {"pheromone_min", c.pheromone_min},
        {"pheromone_max", c.pheromone_max}
    };
}