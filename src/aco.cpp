#include "problem_instance.h"
#include "parameters.h"
#include "pheromone.h"
#include "ant.h"
#include "algorithms/ant_system.h"
#include "algorithms/meeting_ants.h"
#include "utils/visualizer.h"
#include "utils/stats.h"
#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <thread>



// att48 optimal path length: 10628
int main() {
    ProblemInstance problem = load_tsplib_instance("problems/att48.tsp");
    // ProblemInstance problem = load_tsplib_instance("problems/fri26.tsp");
   
    Stats stats = Stats(problem);

    AntSystem AS = AntSystem(problem, defaultConfig, stats);
    MeetingAnts MA = MeetingAnts(problem, defaultConfig, stats);
    // AS.printDebugInfo();
    // int runs = 100;
    AS.debugRun(100);
    stats.printAlgoResults();
    stats.reset();
    MA.debugRun(100);
    stats.printAlgoResults();


    // for(uint16_t i = 0; i < runs; ++i){
    //     // AS.runAlgo(); 
    //     cout << "\r" << "Run " << i << "/" << runs << flush;
    //     MA.runAlgo(); 
    //     // cout << "Best solution found with Ant System: " << AS.runAlgo() << "\n";
    // }
    // cout << "\n";

    return 0;
}