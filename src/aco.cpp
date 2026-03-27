#include "problem_instance.h"
#include "parameters.h"
#include "pheromone.h"
#include "ant.h"
#include <iostream>

int main() {
    ProblemInstance problem = load_tsplib_instance("problems/att48.tsp");
    PheromoneMatrix pheromones = PheromoneMatrix(problem.size_, initial_pheromone, rho);
    Ant ant = Ant(problem.size_, alpha, beta_param, Q);
    ant.startAt(0);
    cout << ant.chooseNextCity(pheromones, problem);
    return 0;
}