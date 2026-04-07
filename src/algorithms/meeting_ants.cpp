#include <cstdint>
#include "meeting_ants.h"

double MeetingAnts::runAlgo(){
    stats.startRun();
    pheromones.reset();
    double bestPath = 1e20;
    uint8_t noChangeCount = 0;

    // while (noChangeCount < 10){
    int i = 0;
    while (i < 2000){
        ++i;
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

double MeetingAnts::stepAlgo(){
    // Spawn ants
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, problem.size_ - 1);

    for(uint32_t i = 0; i < num_ants; ++i){
        ants[i].startAt(distr(gen));
    }

    uint32_t half = problem.size_ / 2;

    // Tour until half the cities are visited
    for(uint32_t i = 0; i < num_ants; ++i){
        while(ants[i].getVisitedCount() < half){
            int next = ants[i].chooseNextCity(pheromones, problem);
            double dist = problem.get_distance(ants[i].getCity(), next);
            ants[i].visitCity(next, dist);
        }
    }

    // Meeting strat
    std::vector<std::vector<int>> mergedTours;
    bool stopEarly = false;

    if(config.use_meeting_strategy){
        mergedTours = meetingPhase();
        stats.logNrOfMerges(mergedTours.size());
        if(mergedTours.size() >= config.meeting_threshold)
            stopEarly = true;
    }

    double bestPath = 1e20;

    // Complete tours unless meeting threshold reached
    if(!stopEarly){
        for(uint32_t i = 0; i < num_ants; ++i){
            if(ants[i].getVisitedCount() == problem.size_) continue;
            double path = ants[i].makePath(pheromones, problem);
            bestPath = std::min(bestPath, path);
        }
    }

    // Eval merged tours
    for(auto &tour : mergedTours){ 
        double len = ants[0].computeTourLength(tour, problem); // TODO: Merge tour should alrdy be in ant
        bestPath = std::min(bestPath, len);
    }

    // Pheromone update
    pheromones.evaporate();

    // Deposit from all ants (merged ants alrdy overwritten)
    for(uint32_t i = 0; i < num_ants; ++i){
        if(ants[i].getVisitedCount() == problem.size_){
            pheromones.deposit(ants[i].getTour(), ants[i].getTourLength());
        }
    }

    // Bound if enabled
    if(config.use_meeting_strategy)
        pheromones.bound();

    return bestPath;
}

std::vector<std::vector<int>> MeetingAnts::meetingPhase(){
    std::vector<std::vector<int>> mergedTours;
    uint32_t n = problem.size_;
    uint32_t meetings = 0;

    std::vector<bool> used(num_ants, false);

    for(uint32_t i = 0; i < num_ants; ++i){
        if(used[i]) continue;

        for(uint32_t j = i + 1; j < num_ants; ++j){
            if(used[j]) continue;

            // Check union 
            std::vector<bool> covered(n, false);
            for(int c : ants[i].getTour()) covered[c] = true;
            for(int c : ants[j].getTour()) covered[c] = true;

            bool allCovered = true;
            for(uint32_t c = 0; c < n; ++c){
                if(!covered[c]) { 
                    allCovered = false; 
                    break; 
                }
            }
            if(!allCovered) continue;

            // Merge tours
            std::vector<int> merged;
            merged.reserve(n);
            std::vector<bool> inMerged(n, false);

            for(int c : ants[i].getTour()){
                if(!inMerged[c]){
                    merged.push_back(c);
                    inMerged[c] = true;
                }
            }
            for(int c : ants[j].getTour()){
                if(!inMerged[c]){
                    merged.push_back(c);
                    inMerged[c] = true;
                }
            }

            if(merged.size() == n){
                mergedTours.push_back(merged);

                // Overwrite ant with merged tour
                ants[i].tour = merged;
                ants[i].visited.assign(n, true);
                ants[i].visited_count = n;
                ants[i].tourLength = ants[i].computeTourLength(merged, problem);

                // Mark ant j as done
                ants[j].visited_count = n;

                used[i] = used[j] = true;
                meetings++;

                if(meetings >= config.meeting_threshold){
                    return mergedTours;
                }
            }
        }
    }

    return mergedTours;
}





