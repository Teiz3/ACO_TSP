#pragma once

#include <cstdint>
#include <vector>
#include <assert.h>

using namespace std;

struct PheromoneMatrix{
    uint32_t size_;
    vector<double> pheremone_matrix_;
    double rho_;

    PheromoneMatrix(uint32_t size, double initial_val, double rho) : 
        size_(size), rho_(rho) {
        pheremone_matrix_ = vector<double>(size_ * size_, initial_val);  
    };

    double get_pheromone(uint32_t from, uint32_t to) const {
        assert((from < size_) && (to < size_));
        return pheremone_matrix_[from * size_ + to];
    }

    void evaporate(){
        for (size_t i = 0; i < (size_*size_); i++){
            pheremone_matrix_[i] *= rho_;
        }
    }
};