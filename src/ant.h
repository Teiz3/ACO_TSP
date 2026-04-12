#include <vector>
#include "pheromone.h"
#include "problem_instance.h"

#pragma once

class Ant {
    public:
        // Constructor
        Ant(int numCities, double alpha, double beta, double Q);

        // Main functions
        void startAt(int city);
        void visitCity(int city, double distance);
        int chooseNextCity(const PheromoneMatrix& pheromone,
                        const ProblemInstance& heuristic);
        // Make a whole tour and return the pathlength
        double makePath(const PheromoneMatrix& pheromone,
                        const ProblemInstance& heuristic);
        
        double computeTourLength(const std::vector<int>& tour,
                         const ProblemInstance& problem) const;

        // Getters
        bool hasVisited(int city) const;
        double getTourLength() const;
        int getCity() const;
        uint32_t getVisitedCount() const;
        const std::vector<int>& getTour() const;
        
        // Params made public for access in meeting ants
        std::vector<int> tour;          // tabu list
        std::vector<bool> visited;      // visited flags
        uint32_t visited_count;
        double tourLength;

        
        
        // Reset
        void reset();

    private:
        // Member vars
        int numCities;
        double alpha;
        double beta;
        int startCity;
        double Q;
};