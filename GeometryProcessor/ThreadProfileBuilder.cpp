#include "ThreadProfileBuilder.hpp"
#include <cmath>
#include <iostream>
#include <vtkVector.h>


namespace  {

  struct Line2D
  {
    double a = 0, b = 0, c = 0;

    Line2D(double a1, double b1, double c1):a(a1), b(b1), c(c1){}
  };

  vtkVector2d CalcLineIntersection(const Line2D& l1, const Line2D& l2)
  {
       const double det = l1.a * l2.b - l2.a * l1.b;

       if (fabs(det) > 0.00001)
       {
          return vtkVector2d((l2.b * l1.c - l1.b *l2.c )/det, (l1.a*l2.c - l2.a *l1.c)/det);
       }

       return vtkVector2d(0, 0);
  }
}

namespace Algo {


std::vector<vtkVector3d> CreateVShapeThreadProfile(double major_dia, double minor_dia, double pitch)
{
    std::vector<vtkVector3d> profile_points;
    const auto DtoR = M_PI/180.0;
    const double H = 0.8660 *pitch;
    const double pby8 = pitch/8.0;
    // y = mx + c => y -mx -c = 0
    Line2D l1(-tan(60*DtoR), 1.0, 0.0);
    Line2D lMajor(0.0, 1, major_dia);
    Line2D lMinor(0.0, 1, minor_dia);

    auto p1 = CalcLineIntersection(l1, lMinor);
    auto p2 = CalcLineIntersection(l1, lMajor);
    auto p3 = vtkVector2d(p2.GetX() + pby8 , p2.GetY() );

    double slop = tan(120.0 * DtoR);
    auto c = p3.GetY() - p3.GetX()*slop;
    Line2D l2(-slop, 1.0, c);
    auto p4 = CalcLineIntersection(l2, lMinor);

    std::cout<<"P1:"<<p1<<" P2:"<<p2<<" P3:"<<p3<<" P4:"<<p4<<"\n";
    profile_points.push_back(vtkVector3d(p1.GetY(), 0.0, p1.GetX()));
    profile_points.push_back(vtkVector3d(p2.GetY(), 0.0, p2.GetX()));
    profile_points.push_back(vtkVector3d(p3.GetY(), 0.0, p3.GetX()));
    profile_points.push_back(vtkVector3d(p4.GetY(), 0.0, p4.GetX()));
    profile_points.push_back(vtkVector3d(p1.GetY(), 0.0, p1.GetX()));

    return profile_points;
}

void CreateButtressThreadProfile()
{

}
}