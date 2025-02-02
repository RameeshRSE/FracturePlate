
#include <vector>


#ifndef SCREW_PLACING_ALGO_HPP
#define SCREW_PLACING_ALGO_HPP

namespace Algo {

struct Screw {
    double x, y, radius;
};
std::vector<Screw> DistributeScrews(int n, double width, double height, double radius);
}

#endif