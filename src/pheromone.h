#pragma once

#include <cstdint>
#include <vector>
#include <assert.h>
#include <iostream>

using namespace std;

struct PheromoneMatrix{
    uint32_t size_;
    vector<double> pheremone_matrix_;
    double rho_;
    double Q_;

    PheromoneMatrix(uint32_t size, double initial_val, double rho, double Q) : 
        size_(size), rho_(rho), Q_(Q) {
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

    void add_pheromone(uint32_t from, uint32_t to, double amount){
        pheremone_matrix_[from * size_ + to] += amount;
    }

    void deposit(vector<int> tour, double tourLength){
        size_t i = 0;
        double amount = Q_ / tourLength;
        for (size_t j = 1; j < tour.size(); j++){
            add_pheromone(tour[i], tour[j], amount);
        }
    }

    void printPheromones() const {
        for(uint32_t i = 0; i < size_; i++){
            for(uint32_t j = 0; j < size_; j++){
                cout << get_pheromone(i, j) << " ";
            }
            cout << "\n";
        } 
    }
};