#include "CoreMath.hpp"
#include <vtkVector.h>

namespace CoreMath {

  double AngleBetween2DLines(const Line2D& l1, const Line2D& l2)
  {
     auto b = l2.a * l1.b - l2.b * l1.a;
     auto a = l1.a *l2.a + l1.b * l2.b;

     if (fabs(a) > 0.00001)
     {
          return  atan(b/a)*1.0/DtoR;
     }

     return 90.0;
  }


 vtkVector2d CalcLineIntersection(const Line2D& l1, const Line2D& l2)
  {
       const double det = l1.a * l2.b - l2.a * l1.b;

       if (fabs(det) > 0.00001)
       {
          return vtkVector2d((l2.b * l1.c - l1.b *l2.c )/det, (l1.a*l2.c - l2.a *l1.c)/det);
       }

       return vtkVector2d();
  }

std::vector<vtkVector3d> CreateConeProfile(double base_diameter, double top_diameter, double height)
{
    std::vector<vtkVector3d> profile_points;
    auto p0= vtkVector2d(0,0);
    auto p1 = vtkVector2d(base_diameter/2.0, 0.0);
    auto p2 = vtkVector2d(top_diameter/2.0, height);
    auto p3 = vtkVector2d(0.0,height);
    std::cout<<"P1:"<<p0<<" P2:"<<p1<<" P3:"<<p2<<" P4:"<<p3<<"\n";
    profile_points.push_back(vtkVector3d(p0.GetX(), 0.0, p0.GetY()));
    profile_points.push_back(vtkVector3d(p1.GetX(), 0.0, p1.GetY()));
    profile_points.push_back(vtkVector3d(p2.GetX(), 0.0, p2.GetY()));
    profile_points.push_back(vtkVector3d(p3.GetX(), 0.0, p3.GetY()));
    profile_points.push_back(vtkVector3d(p0.GetX(), 0.0, p0.GetY()));


    return profile_points;
}

#define LOBES 6
#define STEPS 360 // More steps for smoother curve
std::vector<vtkVector3d> GenerateTorxProfile(double R) {
    std::vector<vtkVector3d> points;
    for (int i = 0; i <= STEPS; ++i) {
        double theta = (2 * M_PI * i) / STEPS;  // Angle from 0 to 2π
        double r = R * (1 - 0.1 * cos(LOBES * theta));  // Torx radial function
    
        double x = r * cos(theta);
        double y = r * sin(theta);
        points.push_back(vtkVector3d(x, y, 0));
    }

    points.push_back(points[0]);

    return points;
}

// Function to generate hexagon vertices
std::vector<vtkVector3d> GenerateHexagon(double height) {
    const double sqrt3 = std::sqrt(3);
    double sideLength = height / sqrt3; // s = h / sqrt(3)

    // Define the hexagon vertices (centered at origin)
    std::vector<vtkVector3d> vertices = {
        {sideLength, 0, 0},
        {sideLength / 2, height / 2, 0},
        {-sideLength / 2, height / 2, 0},
        {-sideLength, 0, 0},
        {-sideLength / 2, -height / 2, 0},
        {sideLength / 2, -height / 2, 0}
    };

    return vertices;
}

}