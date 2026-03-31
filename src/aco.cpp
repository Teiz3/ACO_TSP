#include "problem_instance.h"
#include "parameters.h"
#include "pheromone.h"
#include "ant.h"
#include "algorithms/ant_system.h"
#include "visualizer.h"
#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <thread>



// att48 optimal path length: 10628
int main() {
    ProblemInstance problem = load_tsplib_instance("problems/att48.tsp");
    // ProblemInstance problem = load_tsplib_instance("problems/fri26.tsp");
   
    AntSystem AS = AntSystem(problem, defaultConfig);
    AS.printDebugInfo();
    for(uint16_t i = 0; i < 30; ++i){
        cout << "Best solution found with Ant System: " << AS.runAlgo() << "\n";
    }

    return 0;
}







// std::random_device rd;
// std::mt19937 gen(rd());
// std::uniform_int_distribution<> distr(0, problem.size_ - 1);

// Visualizer visualizer = Visualizer(1920, 1080, "Hellow World");

// double length;

// for (size_t i = 0; i < 500; ++i){
//     visualizer.clear();
//     visualizer.visualizeProblem(problem);
//     // pheromones.printPheromones();
//     ant.startAt(distr(gen));
    
//     length = ant.makePath(pheromones, problem);
//     // cout << length << "\n";
    
//     // Update pheremones:
//     pheromones.evaporate();
//     pheromones.deposit(ant.getTour(), ant.getTourLength());
//     visualizer.visualizeTour(ant.getTour(), problem);
//     visualizer.display();
//     this_thread::sleep_for(chrono::milliseconds(10));
// }
// cout << length << "\n";
// // // pheromones.printPheromones();
// visualizer.keepWindowOpen();