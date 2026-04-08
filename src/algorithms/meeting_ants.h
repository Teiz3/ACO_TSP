/**
 * ant_system.h
 * The original ACO algorithm: Ant System
 */
#include "base.h"
#include "../problem_instance.h"
#include "../pheromone.h"
#include "../parameters.h"
#include "../ant.h"
#include "../utils/stats.h"
#include <vector>
#include <iostream>
#include <random>

#pragma once

class MeetingAnts : public Algorithm{
    public:
        MeetingAnts(ProblemInstance &problem, Config &cfg, Stats &stats) : 
            Algorithm("Meeting ants", problem, cfg, stats){};

        // Run the algorithm and return the best found path value
        double runAlgo();

        // Do a single iteration and return the best pathlength for that iteration
        uint32_t stepAlgo();

        
        std::vector<std::vector<int>> meetingPhase();
};