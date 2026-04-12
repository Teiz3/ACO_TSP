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

#ifndef _WIN32
void Algorithm::debugRun(uint32_t iterations){
    startRun();
    double path;
    for(uint32_t i = 0; i < iterations; ++i){
        cout << "\r" << "Iteration " << i << "/" << iterations << flush;

        visualizer.clear();
        visualizer.visualizeProblem(problem);
        stats.iterate();

        uint32_t idx = stepAlgo();
        path = ants[idx].getTourLength();
        double a = 1 / num_ants;
        for(size_t j = 0; j < num_ants; ++j){
            visualizer.visualizeTour(ants[j].getTour(), problem, sf::Color::Green, a);
        }
        visualizer.visualizeTour(ants[idx].getTour(), problem, sf::Color::Red);
        visualizer.display();
        // this_thread::sleep_for(chrono::milliseconds(50));
    }
    cout << "\n";
    stopRun(path);
    visualizer.keepWindowOpen();
}
#endif

void Algorithm::runBatch(uint32_t num_runs){
      for(uint32_t i = 0; i < num_runs; ++i){
        cout << "\r" << "Run " << i << "/" << num_runs << flush;
        runAlgo(); 
    }
    cout << "\n";
    cout << "Saving batch to json\n";
    stats.exportLog();
}

void Algorithm::startRun(){
    stats.startRun(this);
    pheromones.reset();
}

void Algorithm::stopRun(double best_path){
    stats.stopRun(best_path);
    term->resetTerminator();
}