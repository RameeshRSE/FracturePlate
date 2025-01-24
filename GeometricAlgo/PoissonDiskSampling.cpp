

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <queue>

#include "PoissonDiskSampling.hpp"

namespace Algo 
{

PoissonDiskSampling::PoissonDiskSampling(float width, float height, float radius, int k )
        : width(width), height(height), radius(radius), k(k), cellSize(radius / std::sqrt(2)) {
        gridWidth = static_cast<int>(std::ceil(width / cellSize));
        gridHeight = static_cast<int>(std::ceil(height / cellSize));
        grid.resize(gridWidth * gridHeight, -1);
        srand(static_cast<unsigned>(time(0))); // Seed for random generator
    }


std::vector<Point> PoissonDiskSampling::Generate() {
    std::vector<Point> points;
    std::vector<int> activeList;

    Point firstPoint = RandomPoint();
    points.push_back(firstPoint);
    activeList.push_back(0);
    InsertGrid(firstPoint, 0);

    while (!activeList.empty()) {
        int randIndex = rand() % activeList.size();
        int pointIndex = activeList[randIndex];
        Point currentPoint = points[pointIndex];
        bool found = false;

        for (int i = 0; i < k; i++) {
            Point candidate = GenerateRandomAround(currentPoint);
            if (IsValid(candidate, points)) {
                points.push_back(candidate);
                activeList.push_back(points.size() - 1);
                InsertGrid(candidate, points.size() - 1);
                found = true;
            }
        }

        if (!found) {
            activeList.erase(activeList.begin() + randIndex);
        }
    }

    return points;
}

Point PoissonDiskSampling::RandomPoint() {
    return Point(static_cast<float>(rand()) / RAND_MAX * width,
                    static_cast<float>(rand()) / RAND_MAX * height);
}

Point PoissonDiskSampling::GenerateRandomAround(const Point &point) {
    float r = radius + static_cast<float>(rand()) / RAND_MAX * radius;
    float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
    return Point(point.x + r * std::cos(angle), point.y + r * std::sin(angle));
}

bool PoissonDiskSampling::IsValid(const Point &candidate, const std::vector<Point> &points) {
    if (candidate.x < 0 || candidate.x >= width || candidate.y < 0 || candidate.y >= height) {
        return false;
    }

    int gx = static_cast<int>(candidate.x / cellSize);
    int gy = static_cast<int>(candidate.y / cellSize);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = gx + i;
            int ny = gy + j;
            if (nx >= 0 && ny >= 0 && nx < gridWidth && ny < gridHeight) {
                int neighborIndex = grid[ny * gridWidth + nx];
                if (neighborIndex != -1) {
                    Point neighbor = points[neighborIndex];
                    float dx = candidate.x - neighbor.x;
                    float dy = candidate.y - neighbor.y;
                    if (std::sqrt(dx * dx + dy * dy) < radius) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void PoissonDiskSampling::InsertGrid(const Point &point, int index) {
    int gx = static_cast<int>(point.x / cellSize);
    int gy = static_cast<int>(point.y / cellSize);
    grid[gy * gridWidth + gx] = index;
}
}

