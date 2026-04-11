#ifndef _WIN32
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
        name(name),
        window() {};
        
        void visualizeProblem(ProblemInstance &problem);
        void visualizeTour(const vector<int>& tour, ProblemInstance &problem, 
            sf::Color color = sf::Color::Green, double alpha = 1);
        void keepWindowOpen();
        void display();
        void clear();

        inline void ensureWindow() {
        if (!window.isOpen()) {
            window.create(sf::VideoMode(width, height), name);
        }
    }
    private:
        size_t width;
        size_t height;
        const char* name;
        sf::RenderWindow window;
        sf::Vector2f mapToScreen(Point p, Bounds b);
};
#endif


