#include "ant_system.h"

double AntSystem::runAlgo(){
    startRun();
    double bestPath = 1e20;
    double path = 1e100;

    while (term->canContinue(path)){
        stats.iterate();
        uint32_t idx = stepAlgo();
        path = ants[idx].getTourLength();
        if (path < bestPath){
            bestPath = path;
        }
    }
    stopRun(bestPath);
    return bestPath;
}

uint32_t AntSystem::stepAlgo(){
    // Spawn each ant in a random city
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, problem.size_ -1);
    for(uint32_t i = 0; i < num_ants; ++i){
        ants[i].startAt(distr(gen));
    }

    // Let each ant find a path
    double bestPath = 1e20;
    uint32_t bestAntIdx = 0;
    for(uint32_t i = 0; i < num_ants; ++i){
        double path = ants[i].makePath(pheromones, problem);
        if(path < bestPath){
            bestPath = path;
            bestAntIdx = i;
        }
    }

    // Update pheromones
    pheromones.evaporate();
    for(uint32_t i = 0; i < num_ants; ++i){
        pheromones.deposit(ants[i].getTour(), ants[i].getTourLength());
    }
    return bestAntIdx;
}
