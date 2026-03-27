/**
 * problem_instance.h
 * ProblemInstance class contains the TSP input and node information
 */

#include <cstdint>
#include <vector>
#include "utils.h"
#include <string>
#include <assert.h>
#include <iostream>

#pragma once

using namespace std;

// Various types of edge weights used in TSPLIB
enum EdgeWeightType { EUC_2D, EXPLICIT, GEO, ATT, CEIL_2D };

inline int32_t euc2d_distance(const Vec2d &p1, const Vec2d &p2) {
    return static_cast<int32_t>((p2 - p1).length() + 0.5);
}

inline int32_t ceil_distance(const Vec2d &p1, const Vec2d &p2) {
    return static_cast<int32_t>(std::ceil((p2 - p1).length()));
}

/**
 * Adapted from ACOTSP v1.03 by Thomas Stuetzle
 */
inline int32_t att_distance (const Vec2d &p1, const Vec2d &p2) {
    auto real = std::sqrt((p1 - p2).length_squared() / 10.0);
    auto trun = static_cast<int32_t>(real);
    return static_cast<int32_t>((trun < real) ? trun + 1 : trun);
}

/**
 * Adapted from ACOTSP v1.03 by Thomas Stuetzle
 */
inline int32_t geo_distance (const Vec2d &p1, const Vec2d &p2) {
    double deg, min;
    double lati, latj, longi, longj;
    double q1, q2, q3;

    deg = static_cast<int32_t>(p1.x_);  // Truncate
    min = p1.x_ - deg;
    lati = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

    deg = static_cast<int32_t>(p2.x_);
    min = p2.x_ - deg;
    latj = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

    deg = static_cast<int32_t>(p1.y_);
    min = p1.y_ - deg;
    longi = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

    deg = static_cast<int32_t>(p2.y_);
    min = p2.y_ - deg;
    longj = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

    q1 = cos (longi - longj);
    q2 = cos (lati - latj);
    q3 = cos (lati + latj);
    return static_cast<int32_t>(6378.388 * acos (0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
}


struct ProblemInstance {
    using Point = Vec2d;

    uint32_t size_;
    EdgeWeightType edge_weight_type_ = EUC_2D;
    vector<Point> coords_;
    bool is_symmetric_ = true;
    // Optional name
    string name_;
    double optimal_path_length_;
    vector<double> distance_matrix_;
    
    ProblemInstance(uint32_t size,
                    EdgeWeightType edge_weight_type,
                    vector<Point> coords,
                    bool is_symmetric,
                    string name = "Unknown",
                    double optimal_path_length = -1)
        : size_(size),
          edge_weight_type_(edge_weight_type),
          coords_(move(coords)),
          is_symmetric_(is_symmetric),
          name_(move(name)),
          optimal_path_length_(optimal_path_length) {
        
        // Precompute the distances in the distance matrix
        vector<double> mat(size_ * size_);
        for(uint32_t i = 0; i < size_; i++){
            for(uint32_t j = 0; j < size_; j++){
                mat[i * size_ + j] = get_distance(i, j);
            }
        } 
        distance_matrix_ = mat;
    }

    double get_distance(uint32_t from, uint32_t to) const {
        assert((from < size_) && (to < size_));

        if (!distance_matrix_.empty()) {
            return distance_matrix_[from * size_ + to];
        }

        auto a = coords_[from];
        auto b = coords_[to];
        if (edge_weight_type_ == EUC_2D) {
            return euc2d_distance(a, b);
        }
        if (edge_weight_type_ == CEIL_2D) {
            return ceil_distance(a, b);
        }
        if (edge_weight_type_ == GEO) {
            return geo_distance(a, b);
        }
        if (edge_weight_type_ == ATT) {
            return att_distance(a, b);
        }
        // else edge_weight_type_ == EXPLICIT
        assert(!distance_matrix_.empty());
        return 0;
    }

    void printDistances() const {
        for(uint32_t i = 0; i < size_; i++){
            for(uint32_t j = 0; j < size_; j++){
                cout << get_distance(i, j) << " ";
            }
            cout << "\n";
        } 
    }

};

// Enum for the different lines in the .tsp file
enum class Field {
    NAME, TYPE, DIMENSION, 
    EDGE_WEIGHT_TYPE, EDGE_WEIGHT_FORMAT, 
    NODE_COORD_SECTION, EDGE_WEIGHT_SECTION,
    UNKNOWN
};

/**
 * Matches a line to its coresponding field enum
 * Returns Fiels::UNKNOWN if no result is found
 */
Field getField(const string& line);

/**
 * Tries to load a Traveling Salesman Problem (or ATSP) instance in TSPLIB
 * format from file at 'path'. Only the instances with 'EDGE_WEIGHT_TYPE:
 * EUC_2D' or 'EXPLICIT' are supported.
 *
 * Throws runtime_error if the file is in unsupported format or if an error was
 * encountered.
 *
 * Returns the loaded problem instance.
 */
ProblemInstance load_tsplib_instance(const char *path);