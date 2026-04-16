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
    ProblemInstance att48 = load_tsplib_instance("problems/att48.tsp");
    ProblemInstance eil51 = load_tsplib_instance("problems/eil51.tsp");
    ProblemInstance ch150 = load_tsplib_instance("problems/ch150.tsp");

    ProblemInstance problem = eil51;
   
    Stats stats = Stats(problem, defaultConfig);
    MaxTerminator MaxTerm = MaxTerminator(2000);
    NoChangeTerminator NCTerm = NoChangeTerminator(100, 2000);
    SmallChangeTerminator SCTerm = SmallChangeTerminator(2000);

    AntSystem ASMax = AntSystem(problem, defaultConfig, stats, &MaxTerm);
    AntSystem ASNc = AntSystem(problem, defaultConfig, stats, &NCTerm);
    AntSystem ASSc = AntSystem(problem, defaultConfig, stats, &SCTerm);
    // MeetingAnts MA = MeetingAnts(problem, defaultConfig, stats);
    // AS.printDebugInfo();
    int runs = 100;
    // AS.debugRun(100);

    ASMax.runBatch(runs);
    stats.printAlgoResults();
    stats.reset();

    ASNc.runBatch(runs);
    stats.printAlgoResults();
    stats.reset();
    
    ASSc.runBatch(runs);
    stats.printAlgoResults();
    stats.reset();
    return 0;
}