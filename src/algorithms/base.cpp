#include "base.h"

void Algorithm::printDebugInfo(){
    cout << "\n\t\tAlgorithm:" << name << "\n";
    cout << "================================================\n";
    cout << "PROBLEM: " << problem.name_ << "\tSIZE: " << problem.size_ << "\n";
    cout << "OPTIMAL SOLUTION: " << problem.optimal_path_length_ << "\n";
    cout << "PHEROMONES SIZE: " << pheromones.size_ << "\tQ: " << pheromones.Q_
    << "\tRHO: " << pheromones.rho_;
    cout << "\nNUM ANTS: " << ants.size() << "\n";
    cout << "================================================\n\n";
}