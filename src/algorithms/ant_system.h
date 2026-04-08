/**
 * ant_system.h
 * The original ACO algorithm: Ant System
 */
#include "base.h"
#include <iostream>
#include <random>

#pragma once

class AntSystem : public Algorithm{
    public:
        AntSystem(ProblemInstance &problem, Config &cfg, Stats &stats) : 
            Algorithm("Ant system", problem, cfg, stats){};

        // Run the algorithm and return the best found path value
        double runAlgo();

        uint32_t stepAlgo();
};