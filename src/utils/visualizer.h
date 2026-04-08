#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdint>
#include <vector>
#include "utils.h"
#include "../problem_instance.h"

#pragma once

using Point = Vec2d;
using namespace std;

struct Bounds {
    double minX, maxX, minY, maxY;
};

class Visualizer{
    public:
        Visualizer(size_t w, size_t h, const char* name): 
        width(w),
        height(h),
        window(sf::VideoMode(w, h), name) {};
        
        void visualizeProblem(ProblemInstance &problem);
        void visualizeTour(const vector<int>& tour, ProblemInstance &problem, 
            sf::Color color = sf::Color::Green, double alpha = 1);
        void keepWindowOpen();
        void display();
        void clear();
    private:
        size_t width;
        size_t height;
        sf::RenderWindow window;
        sf::Vector2f mapToScreen(Point p, Bounds b);
};



