#include "Ant.h"
#include <cmath>
#include <limits>
#include <numeric>
#include <random>

static std::mt19937 rng(std::random_device{}());

// Ant constructor
Ant::Ant(int numCities, double alpha, double beta, double Q) 
{
    this->numCities = numCities;  
    this->alpha = alpha;                                // Pheremone attraction stregthn
    this->beta = beta;                                  // Heuristic attraction strength
    this->Q = Q;                                        // Pheromone drop rate
    tour = {};                                          // empty vector of visisted cities
    visited = std::vector<bool>(numCities, false);      // Vector where each city index inits to false
    tourLength = 0.0;                                   
}

// Initializes an ant at a city
void Ant::startAt(int city) {
    reset();
    visitCity(city, 0.0);
}

// Ant visit a city
void Ant::visitCity(int city, double distance) {
    tour.push_back(city);
    visited[city] = true;
    tourLength += distance;
}

// Getter for visited flahs
bool Ant::hasVisited(int city) const {
    return visited[city];
}

// Getter for tourlength
double Ant::getTourLength() const {
    return tourLength;
}

// Getter for ant's current location
int Ant::getCity() const {
    return tour.back();
}

// Getter for entire tour
const std::vector<int>& Ant::getTour() const {
    return tour;
}

// Resets 1 ant
void Ant::reset() {
    tour.clear();
    std::fill(visited.begin(), visited.end(), false);
    tourLength = 0.0;
}