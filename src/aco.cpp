#include "problem_instance.h"
#include "parameters.h"
#include "pheromone.h"
#include <iostream>

int main() {
    ProblemInstance problem = load_tsplib_instance("problems/att48.tsp");
    problem.printDistances();
    return 0;
}