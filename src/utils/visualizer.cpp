#include "visualizer.h"

using namespace std;

Bounds computeBounds(const vector<Point>& pts) {
    Bounds b{1e9, -1e9, 1e9, -1e9};
    for (auto& p : pts) {
        b.minX = std::min(b.minX, p.x_);
        b.maxX = std::max(b.maxX, p.x_);
        b.minY = std::min(b.minY, p.y_);
        b.maxY = std::max(b.maxY, p.y_);
    }
    return b;
}

void Visualizer::visualizeProblem(ProblemInstance &problem){
    // cout << "visualizing...\n";

    Bounds bounds = computeBounds(problem.coords_);

    for (size_t i = 0; i < problem.size_; ++i) {
        auto pos = mapToScreen(problem.coords_[i], bounds);

        sf::CircleShape dot(3);
        dot.setPosition(pos);
        dot.setFillColor(sf::Color::White);

        window.draw(dot);
    }
}

void Visualizer::visualizeTour(const vector<int>& tour, ProblemInstance &problem, sf::Color color, double alpha) {
    Bounds bounds = computeBounds(problem.coords_);
    
    for (size_t i = 0; i < tour.size(); ++i) {
        int a = tour[i];
        int b = tour[(i + 1) % tour.size()];

        auto p1 = mapToScreen(problem.coords_[a], bounds);
        auto p2 = mapToScreen(problem.coords_[b], bounds);

        color.a = std::min(255.0, 25 + (255 * alpha));

        sf::Vertex line[] = {
            sf::Vertex(p1, color),
            sf::Vertex(p2, color)
        };

        window.draw(line, 2, sf::Lines);
    }

}

void  Visualizer::display(){
    window.display();
}
void  Visualizer::clear(){
    window.clear();
}

void Visualizer::keepWindowOpen(){
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == 
            sf::Event::Closed)
                window.close();
        // window.clear();
        // window.display();
    }
}

sf::Vector2f Visualizer::mapToScreen(Point p, Bounds b){
    float x = (p.x_ - b.minX) / (b.maxX - b.minX) * width;
    float y = (p.y_ - b.minY) / (b.maxY - b.minY) * height;
    return {x, y};
}

