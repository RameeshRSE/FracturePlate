#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "ScrewPlacingAlgo.hpp"

namespace  {
using namespace Algo;

bool IsValidPosition(const Screw& newCircle, const std::vector<Screw>& circles, double width, double height) {
    // Check if the circle is within bounds
    if (newCircle.x - newCircle.radius < 0 || newCircle.x + newCircle.radius > width ||
        newCircle.y - newCircle.radius < 0 || newCircle.y + newCircle.radius > height) {
        return false;
    }

    // Check for overlap with existing circles
    for (const auto& circle : circles) {
        double dx = newCircle.x - circle.x;
        double dy = newCircle.y - circle.y;
        double distance = std::sqrt(dx * dx + dy * dy);
        if (distance < newCircle.radius + circle.radius) {
            return false;  // Overlapping
        }
    }

    return true;
}
}

namespace Algo {
std::vector<Screw> DistributeScrews(int n, double width, double height, double radius) {
    std::vector<Screw> circles;
    std::srand(std::time(0));

    for (int i = 0; i < n; ++i) {
        Screw newCircle;
        int attempts = 0, maxAttempts = 1000;  // To avoid infinite loops

        do {
            newCircle.x = radius + (std::rand() / (double)RAND_MAX) * (width - 2 * radius);
            newCircle.y = radius + (std::rand() / (double)RAND_MAX) * (height - 2 * radius);
            newCircle.radius = radius;
            attempts++;
        } while (!IsValidPosition(newCircle, circles, width, height) && attempts < maxAttempts);

        if (attempts < maxAttempts) {
            circles.push_back(newCircle);
        } else {
            std::cerr << "Could not place circle " << i + 1 << " due to space constraints.\n";
        }
    }

    return circles;
}
}
