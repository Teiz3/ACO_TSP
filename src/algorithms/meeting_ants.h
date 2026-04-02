/**
 * ant_system.h
 * The original ACO algorithm: Ant System
 */
#include "../problem_instance.h"
#include "../pheromone.h"
#include "../parameters.h"
#include "../ant.h"
#include "../utils/stats.h"
#include <vector>
#include <iostream>
#include <random>

#pragma once

class MeetingAnts{
    public:
        MeetingAnts(ProblemInstance &problem, Config &cfg, Stats &stats) : 
            problem(problem),
            pheromones(PheromoneMatrix(problem.size_, cfg.initial_pheromone, cfg.rho, cfg.Q)),
            cfg(cfg),
            ants(),
            stats(stats){
                num_ants = cfg.num_ants_equals_num_cities ? problem.size_ : cfg.num_ants;
                ants.reserve(num_ants);
                for (uint32_t i = 0; i < num_ants; ++i){
                    ants.push_back(Ant(problem.size_, cfg.alpha, cfg.beta, cfg.Q));
                }
            };

        // Run the algorithm and return the best found path value
        double runAlgo();

        // Do a single iteration and return the best pathlength for that iteration
        double stepAlgo();

        
        std::vector<std::vector<int>> meetingPhase();

        void printDebugInfo();
    private:
        ProblemInstance problem;
        PheromoneMatrix pheromones;
        Config config;
        vector<Ant> ants;
        uint32_t num_ants;
        Stats &stats;
};