/**
 * Stats.h
 * Stats module to keep track and log statistics and other important data
 * This class also makes the result logs
 */
#pragma once
#include <cstdint>
#include <vector>
#include <chrono>
#include <format>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include "../problem_instance.h"
#include "../parameters.h"
#include "utils.h"
#include "json.hpp"
using ordered_json = nlohmann::ordered_json;
using json = nlohmann::json;

class Algorithm; // Forward declaration

using namespace std;

struct BatchStats{
    uint32_t minIterations;
    uint32_t maxIterations;
    double avgIterations;

    double minPath;
    double maxPath;
    double avgPath;

    uint32_t totalTime; // Miliseconds
    double avgTime;     // MiliSeconds

};

class Stats{
    public:
        Stats(ProblemInstance& problem, Config& config) : problem(problem), config(config) {};

        /**
         * @brief Start a new run tracker.
         * @param algo_name The name of the algorithm that performs this run.
         */
        void startRun(Algorithm* algo);
        /**
         * @brief Stop tracking the current run and store the results.
         * @param path_length The best path length found in this run.
         */
        void stopRun(double path_length);

        /**
         * @brief Prints the info of the last run.
         */
        void printRunInfo();
        /**
         * @brief Prints the runinfo of run runId to stdout.
         * @param runId The index of the run to print.
         */
        void printRunInfo(int runId);

        /**
         * @brief Increments iteration counter
         * @note Should be called once for each iteration of the algorithm
         */
        void iterate();

        /**
         * @brief Store the number of merges in Merging Ant algorithm.
         * @param merge_count The number of merges in that iteration.
         */
        void logNrOfMerges(uint32_t merge_count);

        /**
         * @brief Print a full report on all stored runs.
         */
        void printAlgoResults();

        /**
         * @brief Resets all stored statistics
         */
        void reset();

        /**
         * @brief exports all logs and stats to a json file.
         */
        void exportLog();

        
    private:
        int currentRun = -1;
        chrono::steady_clock::time_point batch_start;
        chrono::milliseconds batch_duration;
        
        // Algorithm used
        Algorithm* algo;
        
        // Timings and iteration counts
        vector<uint32_t> iteration_counts = vector<uint32_t>();
        chrono::steady_clock::time_point run_start;
        vector<chrono::milliseconds> run_times = vector<chrono::milliseconds>();

        // Run results
        vector<double> path_lengths = vector<double>();

        // Merging ant specific stats
        vector<uint32_t> num_merges = vector<uint32_t>();

        // Algorithm parameters and other metadata
        ProblemInstance &problem;
        Config &config;
        
        // Compute stats
        BatchStats computeStats();
};

