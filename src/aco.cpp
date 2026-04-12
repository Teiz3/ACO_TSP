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
    MaxTerminator MaxTerm = MaxTerminator(2000);
    NoChangeTerminator NCTerm = NoChangeTerminator(100, 2000);

    AntSystem AS1 = AntSystem(problem, defaultConfig, stats, &MaxTerm);
    AntSystem AS2 = AntSystem(problem, defaultConfig, stats, &NCTerm);
    // MeetingAnts MA = MeetingAnts(problem, defaultConfig, stats);
    // AS.printDebugInfo();
    // int runs = 100;
    // AS.debugRun(100);

    // AS1.runBatch(100);
    // stats.printAlgoResults();
    // stats.reset();
    AS2.runBatch(10);
    stats.printAlgoResults();
    return 0;
}