/**
 * Base class for the algorithms
 */
#pragma once
#include "../problem_instance.h"
#include "../pheromone.h"
#include "../parameters.h"
#include "../ant.h"
#include "../utils/stats.h"
#include <vector>

class Algorithm{
    protected:
        const char* name; // Name of the algorithm
        ProblemInstance problem;
        PheromoneMatrix pheromones;
        Config cfg;
        vector<Ant> ants;
        size_t num_ants;
        Stats &stats;

    public:
        Algorithm(const char* name, ProblemInstance &problem, Config &cfg, Stats &stats) : 
            name(name),
            problem(problem),
            pheromones(PheromoneMatrix(problem.size_, cfg.initial_pheromone, cfg.rho, cfg.Q)),
            cfg(cfg),
            ants(),
            stats(stats) {
                num_ants = cfg.num_ants_equals_num_cities ? problem.size_ : cfg.num_ants;
                ants.reserve(num_ants);
                for(size_t i = 0; i < num_ants; ++i){
                    ants.push_back(Ant(problem.size_, cfg.alpha, cfg.beta, cfg.Q));
                }
            };
        
        virtual double runAlgo() = 0;
        virtual double stepAlgo() = 0;
        void printDebugInfo();

        /**
         * @brief Runs the algorithm num_runs times and reports the results.
         */
        void runBatch(uint32_t num_runs);
        
        /**
         * @brief Run a debug session with extra reporting and visualization.
         */
        void debugRun();

        virtual ~Algorithm() {};
};