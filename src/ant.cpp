#include "ant.h"
#include <cmath>
#include <limits>
#include <numeric>
#include <random>

static std::mt19937 rng(std::random_device{}());

// Ant constructor
Ant::Ant(int numCities, double alpha, double beta, double Q) :
    numCities(numCities),           // Pheremone attraction stregthn
    alpha(alpha),                   // Heuristic attraction strength
    beta(beta),                     // Pheromone drop rate
    Q(Q),                           // empty vector of visisted cities
    tour(),                         // Vector where each city index inits to false
    visited(numCities, false),
    visited_count(0),
    tourLength(0) {}

// Initializes an ant at a city
void Ant::startAt(int city) {
    reset();
    visitCity(city, 0.0);
    startCity = city;
}

// Ant visit a city
void Ant::visitCity(int city, double distance) {
    tour.push_back(city);
    visited[city] = true;
    visited_count++;
    tourLength += distance;
}

int Ant::chooseNextCity(const PheromoneMatrix& pheromones,
                        const ProblemInstance& heuristics)
{
    int current = getCity();

    std::vector<double> probabilities(numCities, 0.0);
    double sum = 0.0;

    // Eq 3
    for (int i = 0; i < numCities; i++) {
        if (!visited[i]) {
            double eta = (1 / heuristics.get_distance(current, i));
            double tau = std::pow(pheromones.get_pheromone(current, i), alpha);
            eta = std::pow(eta, beta);
            probabilities[i] = tau * eta;
            sum += probabilities[i];
        }
    }

    // Roulette wheel selection, made by chatje
    std::uniform_real_distribution<double> dist(0.0, sum);
    double r = dist(rng);

    double cumulative = 0.0;
    for (int j = 0; j < numCities; j++) {
        if (!visited[j]) {
            cumulative += probabilities[j];
            if (cumulative >= r) {
                return j;
            }
        }
    }
    return -1;
}

double Ant::makePath(const PheromoneMatrix& pheromone, const ProblemInstance& heuristic){
    
    while (visited_count < heuristic.size_){
        int next = chooseNextCity(pheromone, heuristic);
        assert(!hasVisited(next));
        double dist = heuristic.get_distance(getCity(), next);
        visitCity(next, dist);
    }
    // Complete tour by going back to the original city
    visitCity(startCity, heuristic.get_distance(getCity(), startCity));

    return getTourLength();
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

uint32_t Ant::getVisitedCount() const {
    return visited_count;
}


// Resets 1 ant
void Ant::reset() {
    tour.clear();
    std::fill(visited.begin(), visited.end(), false);
    visited_count = 0;
    tourLength = 0.0;
}

double Ant::computeTourLength(const std::vector<int>& tour,
                              const ProblemInstance& problem) const
{
    if (tour.empty()) return 0.0;

    double length = 0.0;

    for (size_t i = 0; i < tour.size() - 1; ++i) {
        length += problem.get_distance(tour[i], tour[i + 1]);
    }

    length += problem.get_distance(tour.back(), tour.front());

    return length;
}
