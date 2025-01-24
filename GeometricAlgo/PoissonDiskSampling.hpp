#include <vector>

#ifndef POISSON_DISK_SAMPLING_HPP
#define POISSON_DISK_SAMPLING_HPP

namespace Algo {
struct Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {}
};

class PoissonDiskSampling {
public:
    PoissonDiskSampling(float width, float height, float radius, int k = 30);
    std::vector<Point> Generate();

private:
    float width, height, radius, cellSize;
    int k, gridWidth, gridHeight;
    std::vector<int> grid;
    Point RandomPoint();
    Point GenerateRandomAround(const Point &point);
    bool IsValid(const Point &candidate, const std::vector<Point> &points);
    void InsertGrid(const Point &point, int index);
};

}
#endif
