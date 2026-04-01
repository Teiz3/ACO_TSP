#include "ant_system.h"

double AntSystem::runAlgo(){
    pheromones.reset();
    double bestPath = 1e20;
    uint8_t noChangeCount = 0;

    while (noChangeCount < 1){
        double path = stepAlgo();
        if (path < bestPath){
            bestPath = path;
            noChangeCount = 0;
        }else{
            noChangeCount++;
        }
    }
    return bestPath;
}

double AntSystem::stepAlgo(){
    // Spawn each ant in a random city
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, problem.size_ -1);
    for(uint32_t i = 0; i < num_ants; ++i){
        ants[i].startAt(distr(gen));
    }

    // Let each ant find a path
    double bestPath = 1e20;
    for(uint32_t i = 0; i < num_ants; ++i){
        double path = ants[i].makePath(pheromones, problem);
        bestPath = min(bestPath, path);
    }

    // Update pheromones
    pheromones.evaporate();
    for(uint32_t i = 0; i < num_ants; ++i){
        pheromones.deposit(ants[i].getTour(), ants[i].getTourLength());
    }
    return bestPath;
}

void AntSystem::printDebugInfo(){
    cout << "\n\tAnt System instance\n";
    cout << "=========================================\n";
    cout << "PROBLEM: " << problem.name_ << "\tSIZE: " << problem.size_ << "\n";
    cout << "OPTIMAL SOLUTION: " << problem.optimal_path_length_ << "\n";
    cout << "PHEROMONES SIZE: " << pheromones.size_ << "\tQ: " << pheromones.Q_
    << "\tRHO: " << pheromones.rho_;
    cout << "\nNUM ANTS: " << ants.size() << "\n";
    cout << "=========================================\n\n";
}