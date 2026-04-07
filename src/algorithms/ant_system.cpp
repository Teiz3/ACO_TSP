#include "ant_system.h"

double AntSystem::runAlgo(){
    stats.startRun();
    pheromones.reset();
    double bestPath = 1e20;
    uint8_t noChangeCount = 0;

    while (noChangeCount < 10){
        stats.iterate();
        double path = stepAlgo();
        if (path < bestPath){
            bestPath = path;
            noChangeCount = 0;
        }else{
            noChangeCount++;
        }
    }
    stats.stopRun(bestPath);
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
