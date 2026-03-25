#include "problem_instance.h"
#include <iostream>

int main() {
    ProblemInstance problem = load_tsplib_instance("problems/att48.tsp");
    return 0;
}