#include "problem_instance.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

Field getField(const string& line){
    if (line.find("NAME") == 0) return Field::NAME;
    if (line.find("TYPE") == 0) return Field::TYPE;
    if (line.find("DIMENSION") != string::npos) return Field::DIMENSION;
    if (line.find("EDGE_WEIGHT_TYPE") != string::npos) return Field::EDGE_WEIGHT_TYPE;
    if (line.find("EDGE_WEIGHT_FORMAT") != string::npos) return Field::EDGE_WEIGHT_FORMAT;
    if (line.find("NODE_COORD_SECTION") != string::npos) return Field::NODE_COORD_SECTION;
    if (line.find("EDGE_WEIGHT_SECTION") != string::npos) return Field::EDGE_WEIGHT_SECTION;
    return Field::UNKNOWN;
}

// This comes from https://stackoverflow.com/a/217605
// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// This comes from https://stackoverflow.com/a/217605
// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// This comes from https://stackoverflow.com/a/217605
// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

ProblemInstance load_tsplib_instance(const char* path){
    using namespace std;
    enum EdgeWeightFormat { UPPER_DIAG_ROW, LOWER_DIAG_ROW, UPPER_ROW, FUNCTION };

    ifstream in(path);
    if (!in.is_open()){
        throw runtime_error(string("Cannot open TSP instance file: ") + path);
    }

    string line;

    uint32_t dimension = 0;
    vector<double> distances;
    vector<Vec2d> coords;
    EdgeWeightType edge_weight_type{EUC_2D};
    EdgeWeightFormat edge_weight_format{UPPER_DIAG_ROW};
    string name = "Unknown";
    bool is_symmetric = true;

    cout << "Loading TSP instance from file: " << path << "\n";

    while (getline(in, line)){
        // cout << '\t' << line << endl;
        switch (getField(line)){
            case Field::NAME: {   
                name = line.substr(line.find(':') + 1);
                trim(name);
                break;
            }

            case Field::TYPE:{
                if (line.find(" TSP") != string::npos) {
                    is_symmetric = true;
                } else if (line.find(" ATSP") != string::npos) {
                    is_symmetric = false;
                } else {
                    throw runtime_error("Unknown problem type");
                }
                break;
            }

            case Field::DIMENSION: {    
                istringstream line_in(line.substr(line.find(':') + 1));
                if (!(line_in >> dimension)) {
                    throw runtime_error(string("Cannot read instance dimension"));
                }
                break;
            }
            
            case Field::EDGE_WEIGHT_TYPE: {
                if (line.find(" EUC_2D") != string::npos) {
                    edge_weight_type = EUC_2D;
                } else if (line.find(" CEIL_2D") != string::npos) {
                    edge_weight_type = CEIL_2D;
                } else if (line.find(" EXPLICIT") != string::npos) {
                    edge_weight_type = EXPLICIT;
                } else if (line.find(" GEO") != string::npos) {
                    edge_weight_type = GEO;
                } else if (line.find(" ATT") != string::npos) {
                    edge_weight_type = ATT;
                } else {
                    throw runtime_error(string("Unsupported edge weight type"));
                }
                break;
            }
            
            case Field::EDGE_WEIGHT_FORMAT: {
                if (line.find(" UPPER_DIAG_ROW") != string::npos) {
                    edge_weight_format = UPPER_DIAG_ROW;
                } else if (line.find(" LOWER_DIAG_ROW") != string::npos) {
                    edge_weight_format = LOWER_DIAG_ROW;
                } else if (line.find(" UPPER_ROW") != string::npos) {
                    edge_weight_format = UPPER_ROW;
                } else if (line.find(" FUNCTION") != string::npos) {
                    edge_weight_format = FUNCTION;
                } else {
                    throw runtime_error(string("Unsupported edge weight format"));
                }
                break;
            }
                
            case Field::NODE_COORD_SECTION: {

                while (coords.size() < dimension && getline(in, line)) {
                    if (line.find("EOF") != string::npos) {
                        break ;
                    }
                    istringstream line_in(line);
                    uint32_t id;
                    Vec2d point {};
                    if (line_in >> id >> point.x_ >> point.y_) {
                        coords.push_back(point);
                    } else {
                        cerr << "Error while reading coordinates! A pair of floats was expected.";
                        abort();  // We should not continue without checking the input file first
                    }
                }
                break;
            }
                
            case Field::EDGE_WEIGHT_SECTION: {

                assert(dimension > 0);
                if (edge_weight_type != EXPLICIT) {
                    throw runtime_error("Expected EXPLICIT edge weight type");
                }
                
                if (edge_weight_format == UPPER_DIAG_ROW) {
                    distances.resize(dimension * dimension);
                    
                    uint32_t row = 0;
                    uint32_t col = 0;
                    while (row < dimension && getline(in, line)) {
                        istringstream line_in(line);
                        double distance;
                        while (line_in >> distance) {
                            distances.at(row * dimension + col) = distance;
                            distances.at(col * dimension + row) = distance;
                            ++col;
                            if (col == dimension) {
                                ++row;
                                col = row;
                            }
                        }
                    }
                } else if (edge_weight_format == UPPER_ROW) {
                    distances.resize(dimension * dimension);
                    
                    uint32_t row = 0;
                    uint32_t col = 1;
                    while (row < dimension && getline(in, line)) {
                        istringstream line_in(line);
                        double distance;
                        while (line_in >> distance) {
                            distances.at(row * dimension + col) = distance;
                            distances.at(col * dimension + row) = distance;
                            ++col;
                            if (col == dimension) {
                                ++row;
                                col = row + 1;
                            }
                        }
                    }
                } else if (edge_weight_format == LOWER_DIAG_ROW) {
                    distances.resize(dimension * dimension, 0);
                    
                    uint32_t row = 0;
                    uint32_t col = 0;
                    while (row < dimension && getline(in, line)) {
                        istringstream line_in(line);
                        double distance;
                        while (line_in >> distance) {
                            distances.at(row * dimension + col) = distance;
                            distances.at(col * dimension + row) = distance;
                            ++col;
                            if (col == row + 1) {
                                ++row;
                                col = 0;
                                if (row == dimension) {
                                    break ;
                                }
                            }
                        }
                    }
                } else {
                    distances.reserve(dimension * dimension);
                    while (getline(in, line)) {
                        if (line.find("EOF") != string::npos) {
                            break;
                        }
                        istringstream line_in(line);
                        double distance;
                        while (line_in >> distance) {
                            distances.push_back(distance);
                        }
                    }
                }
                assert(distances.size() == dimension * dimension);
                break;
            }
            default:
            case Field::UNKNOWN: {
                break;
            }
        }
                
        
    }
    in.close();
    assert(dimension > 2);

    return ProblemInstance(dimension, edge_weight_type, coords, is_symmetric, name);
}