
#include<cmath>
#include<vtkVector.h>

#ifndef CORE_MATH_HPP
#define CORE_MATH_HPP

namespace CoreMath {

 const auto DtoR = M_PI/180.0;

  struct Line2D
  {
    double a = 0, b = 0, c = 0;

    Line2D(double a1, double b1, double c1):a(a1), b(b1), c(c1){}
  };

  vtkVector2d CalcLineIntersection(const Line2D& l1, const Line2D& l2);
  double AngleBetween2DLines(const Line2D& l1, const Line2D& l2);
  std::vector<vtkVector3d> GenerateTorxProfile(double R);
  std::vector<vtkVector3d> GenerateHexagon(double height);
  std::vector<vtkVector3d> CreateConeProfile(double base_diameter, double top_diameter, double height);
}

#endif