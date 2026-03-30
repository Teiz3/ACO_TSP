#include "problem_instance.h"
#include "parameters.h"
#include "pheromone.h"
#include "ant.h"
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
    PheromoneMatrix pheromones = PheromoneMatrix(problem.size_, initial_pheromone, rho, Q);
    Ant ant = Ant(problem.size_, alpha, beta_param, Q);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, problem.size_ - 1);
    
    Visualizer visualizer = Visualizer(1920, 1080, "Hellow World");
    
    double length;
    
    for (size_t i = 0; i < 2000; ++i){
        visualizer.clear();
        visualizer.visualizeProblem(problem);
        // pheromones.printPheromones();
        ant.startAt(distr(gen));
        
        length = ant.makePath(pheromones, problem);
        // cout << length << "\n";
        
        // Update pheremones:
        pheromones.evaporate();
        pheromones.deposit(ant.getTour(), ant.getTourLength());
        visualizer.visualizeTour(ant.getTour(), problem);
        visualizer.display();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    cout << length << "\n";
    // // pheromones.printPheromones();
    visualizer.keepWindowOpen();
    return 0;
}