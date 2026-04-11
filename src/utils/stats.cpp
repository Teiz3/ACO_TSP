#include "stats.h"

void Stats::startRun(const char* algo_name){
    algorithm_name = algo_name;
    if(currentRun == -1) batch_start = chrono::steady_clock::now();
    ++currentRun;
    iteration_counts.push_back(0);
    num_merges.push_back(0);
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

void Stats::logNrOfMerges(uint32_t merge_count){
    num_merges[currentRun] += merge_count;
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
    
    cout << "\n  " <<  algorithm_name << " BATCH INFO: " << problem.name_ << " (" << num_runs << " runs)\n";
    cout << "================================================\n";
    cout << "  PATHS\n"
         << "Best:\t\t" << *minmaxPath.first << "\t(%): " << *minmaxPath.first / problem.optimal_path_length_
         << "\nWorst:\t\t" << *minmaxPath.second << "\t(%): " << *minmaxPath.second / problem.optimal_path_length_
         << "\nAverage:\t" << avrPath << "\t(%): " << avrPath / problem.optimal_path_length_ << "\n";
             
    cout << "  ITERATIONS\n";
    cout << "Best:\t\t" << *minmaxIt.first 
         << "\nWorst:\t\t" << *minmaxIt.second
         << "\nAverage\t\t" << avrIt << "\n";
    
    cout << "\nRuntime: " << (batch_duration.count() / 1000.0) << "[s]\n";
    cout << "Average runtime per run: " << avrT << "[ms]\n";

    cout << "Number of merges each run:\n";
    for(int i = 0; i < currentRun; ++i){
        cout << num_merges.at(i) << " ";
    }
    cout << "\n";
}

void Stats::reset(){
    currentRun = -1;
    iteration_counts.clear();
    path_lengths.clear();
    num_merges.clear();
}

void Stats::exportLog(){
    ordered_json j;
    auto now = std::chrono::system_clock::now();
    auto now_sec = std::chrono::time_point_cast<std::chrono::seconds>(now);

    j["problem"] = problem.name_;
    j["algorithm"] = algorithm_name;
    j["timings"] = json{
        {"date", to_string(now)},
        {"runtime_sec", to_seconds(batch_duration)}
    };
    j["config"] = to_json(config);
    j["solution"] = problem.optimal_path_length_;
    j["results"] = json{
        {"iteration_counts", iteration_counts},
        {"path_lengths", path_lengths},
        {"num_merges", num_merges}
    };

    std::string filename = std::format(
    "results/{}-{}-{:%Y-%m-%d-%H-%M-%S}.json",
    algorithm_name,
    problem.name_,
    now_sec
    );
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    file << j.dump(2);
}
