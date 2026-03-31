/**
 * ant_system.h
 * The original ACO algorithm: Ant System
 */
#include "../problem_instance.h"
#include "../pheromone.h"
#include "../parameters.h"
#include "../ant.h"
#include <vector>
#include <iostream>
#include <random>

class AntSystem{
    public:
        AntSystem(ProblemInstance &problem, Config &cfg) : 
            problem(problem),
            pheromones(PheromoneMatrix(problem.size_, cfg.initial_pheromone, cfg.rho, cfg.Q)),
            cfg(cfg),
            ants() {
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


        void printDebugInfo();
    private:
        ProblemInstance problem;
        PheromoneMatrix pheromones;
        Config cfg;
        vector<Ant> ants;
        uint32_t num_ants;
};