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
    // ProblemInstance a280 = load_tsplib_instance("problems/a280.tsp");//
    // ProblemInstance att48 = load_tsplib_instance("problems/att48.tsp");//
    // ProblemInstance berlin52 = load_tsplib_instance("problems/berlin52.tsp");//
    // ProblemInstance bier127 = load_tsplib_instance("problems/bier127.tsp");//
    // ProblemInstance ch130 = load_tsplib_instance("problems/ch130.tsp");//
    // ProblemInstance ch150 = load_tsplib_instance("problems/ch150.tsp");//
    // ProblemInstance eil51 = load_tsplib_instance("problems/eil51.tsp");//
    // ProblemInstance eil76 = load_tsplib_instance("problems/eil76.tsp");//
    // ProblemInstance eil101 = load_tsplib_instance("problems/eil101.tsp");//
    // ProblemInstance fri26 = load_tsplib_instance("problems/fri26.tsp");//
    ProblemInstance kroA200 = load_tsplib_instance("problems/kroA200.tsp");//
    ProblemInstance lin105 = load_tsplib_instance("problems/lin105.tsp");//
    ProblemInstance lin318 = load_tsplib_instance("problems/lin318.tsp");//
    ProblemInstance pr76 = load_tsplib_instance("problems/pr76.tsp");//
    ProblemInstance pr124 = load_tsplib_instance("problems/pr124.tsp");//
    ProblemInstance pr136 = load_tsplib_instance("problems/pr136.tsp");//
    ProblemInstance rat575 = load_tsplib_instance("problems/rat575.tsp");
    ProblemInstance rd400 = load_tsplib_instance("problems/rd400.tsp");//
    ProblemInstance st70 = load_tsplib_instance("problems/st70.tsp");//
    ProblemInstance tsp225 = load_tsplib_instance("problems/tsp225.tsp");//

    ProblemInstance arr[] = {kroA200, lin105, lin318, pr124, pr136, rat575, rd400, tsp225};

    for(size_t i = 0; i < size(arr); ++i){

        
        ProblemInstance problem = arr[i];
        
        Stats stats = Stats(problem, defaultConfig);
        NoChangeTerminator NCTerm = NoChangeTerminator(100, 2000);
        
        // AntSystem ASMax = AntSystem(problem, defaultConfig, stats, &MaxTerm);
        AntSystem ASNc = AntSystem(problem, defaultConfig, stats, &NCTerm);
        // AntSystem ASSc = AntSystem(problem, defaultConfig, stats, &SCTerm);
        MeetingAnts MA = MeetingAnts(problem, defaultConfig, stats, &NCTerm);
        
        
        int runs = 100;
        
        ASNc.runBatch(runs);
        stats.printAlgoResults();
        stats.reset();
        
        MA.runBatch(runs);
        stats.printAlgoResults();
        stats.reset();
    }
    
    return 0;
}