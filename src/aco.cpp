#include "problem_instance.h"
#include "parameters.h"
#include "algorithms/ant_system.h"
#include "algorithms/meeting_ants.h"
#include "utils/stats.h"
#include <iostream>
#include <chrono>
#include <thread>



// att48 optimal path length: 10628
int main() {
    ProblemInstance problem = load_tsplib_instance("problems/att48.tsp");
    // ProblemInstance problem = load_tsplib_instance("problems/fri26.tsp");
   
    Stats stats = Stats(problem, defaultConfig);

    AntSystem AS = AntSystem(problem, defaultConfig, stats);
    MeetingAnts MA = MeetingAnts(problem, defaultConfig, stats);
    // AS.printDebugInfo();
    // int runs = 100;
    // AS.debugRun(100);
    AS.runBatch(100);
    // stats.printAlgoResults();
    // stats.reset();
    // MA.debugRun(100);
    // MA.runBatch(2);
    stats.printAlgoResults();
    return 0;
}