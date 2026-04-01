#include "stats.h"

void Stats::startRun(){
    if(currentRun == -1) batch_start = chrono::steady_clock::now();
    ++currentRun;
    iteration_counts.push_back(0);
    // Start run timer
    run_start = chrono::steady_clock::now();
}

void Stats::stopRun(double path_lenght){
    // Stop run timer
    chrono::milliseconds run_duration = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - run_start);
    run_times.push_back(run_duration);
    path_lengths.push_back(path_lenght);
    // Update batch duration
    batch_duration = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - batch_start);
}

void Stats::iterate(){
    ++iteration_counts[currentRun];
}

void Stats::printRunInfo(){
    printRunInfo(currentRun);
}

void Stats::printRunInfo(int runId){
    chrono::milliseconds run_duration;
    assert(run_times.size() > 0);
    try{
        run_duration = run_times.at(runId);
    }catch (out_of_range const&){
        cout << "[ERROR] - invalid runId\n";
        cout << "runId must 0-" << run_times.size() << "\n";
        return;
    }
    

    cout << "\n\tRUNINFO RUN: " << problem.name_ << " (" << runId + 1 << "/" << currentRun+1 << ")\n";
    cout << "================================================\n";
    cout << "Iterations: " << iteration_counts[runId] << "\t";
    cout << "Runtime: ";
    if (run_duration.count() < 1000){
        cout << run_duration.count() << "\t[ms]\n";
    }else{
        cout << run_duration.count() / 1000 << "\t[s]\n";
    }
    cout << "Path length: " << path_lengths[runId]
         <<  "\t(%): " << (path_lengths[runId] / problem.optimal_path_length_) << "\n";
    cout << "\n";
}

void Stats::printAlgoResults(){
    assert(currentRun >= 0);
    
    uint32_t num_runs = currentRun + 1;

    auto minmaxIt = minmax_element(iteration_counts.begin(), iteration_counts.end());
    uint32_t sumIt = accumulate(iteration_counts.begin(), iteration_counts.end(), 0);
    float avrIt = sumIt / num_runs;
    
    chrono::milliseconds sumT = accumulate(run_times.begin(), run_times.end(), chrono::milliseconds(0));
    float avrT = (sumT.count() / num_runs); // Convert to seconds

    auto minmaxPath = minmax_element(path_lengths.begin(), path_lengths.end());
    double sumPath = accumulate(path_lengths.begin(), path_lengths.end(), 0);
    double avrPath = sumPath / num_runs;
    
    cout << "\n\t\tBATCH INFO: " << problem.name_ << " (" << num_runs << " runs)\n";
    cout << "================================================\n";
    cout << "  PATHS\n"
         << "Best:\t\t" << *minmaxPath.first << "\t(%): " << *minmaxPath.first / problem.optimal_path_length_
         << "\nWorst:\t\t" << *minmaxPath.second << "\t(%): " << *minmaxPath.second / problem.optimal_path_length_
         << "\nAverage:\t" << avrPath << "\t(%): " << avrPath / problem.optimal_path_length_ << "\n";
             
    cout << "  ITERATIONS\n";
    cout << "Best:\t\t" << *minmaxIt.first 
         << "\nWorst:\t\t" << *minmaxIt.second
         << "\nAverage\t\t" << avrIt << "\n";
    
    cout << "\nRuntime: " << batch_duration.count() << "[ms]\n";
    cout << "Average runtime per run: " << avrT << "[ms]\n";
}
