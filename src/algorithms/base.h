/**
 * Base class for the algorithms
 */
#pragma once
#include "../problem_instance.h"
#include "../pheromone.h"
#include "../parameters.h"
#include "../ant.h"
#include "../utils/stats.h"
#ifndef _WIN32
#include "../utils/visualizer.h"
#endif
#include <vector>
#include <thread>

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
            stats(stats)
#ifndef _WIN32
            ,visualizer(Visualizer(1280, 720, name)) 
#endif
            
            {
                num_ants = cfg.num_ants_equals_num_cities ? problem.size_ : cfg.num_ants;
                ants.reserve(num_ants);
                for(size_t i = 0; i < num_ants; ++i){
                    ants.push_back(Ant(problem.size_, cfg.alpha, cfg.beta, cfg.Q));
                }
            };
        
        /**
         * @brief Runs a single full run of the algorithm.
         * @note This function calls startRun(), so it is not needed to call yourself.
         */
        virtual double runAlgo() = 0;

        /**
         * @brief Runs a single iteration (each ant makes only one path).
         * @note Requires that startRun() is called at least once before.
         * @return The index of the ant that found the best path.
         */
        virtual uint32_t stepAlgo() = 0;
        
        /**
         * @brief Initializes the algorithm for a run.
         */
        virtual void startRun();

        /**
         * @brief Finilizes the run
         */
        virtual void stopRun(double best_path);
        
        void printDebugInfo();
        
        

        /**
         * @brief Runs the algorithm num_runs times and reports the results.
         */
        void runBatch(uint32_t num_runs);
            
        virtual ~Algorithm() {};

#ifndef _WIN32
        /**
         * @brief Run a debug run with extra reporting and visualization.
         * @param runs The number of iterations to do.
         */
        void debugRun(uint32_t iterations);

    private:
        Visualizer visualizer;
#endif
};