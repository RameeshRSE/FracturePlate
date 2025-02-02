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
    Line2D lVertical(1.0, 0.0, 0.0);
    auto p1 = vtkVector2d(base_diameter/2.0, 0.0);
    auto p2 = vtkVector2d(top_diameter/2.0, height);
    auto slop = (p2.GetY() - p1.GetY())/(p2.GetX() - p1.GetX()); 
    auto c = p1.GetY() - slop * p1.GetX();
    Line2D l2(-slop, 1.0, c);
    Line2D lBase(0.0, 1, base_diameter);
    Line2D lTop(0.0, 1, top_diameter);
    auto p0= vtkVector2d(0,0);
    p1 = CalcLineIntersection(l2, lBase);
    p2 = CalcLineIntersection(l2, lTop);
    auto p3 = vtkVector2d(0,height);
    std::cout<<"P1:"<<p0<<" P2:"<<p1<<" P3:"<<p2<<" P4:"<<p3<<"\n";
    std::cout<<"Cone Angle ="<<AngleBetween2DLines(l2, lVertical)<<"\n";
    profile_points.push_back(vtkVector3d(p0.GetY(), 0.0, p0.GetX()));
    profile_points.push_back(vtkVector3d(p1.GetY(), 0.0, p1.GetX()));
    profile_points.push_back(vtkVector3d(p2.GetY(), 0.0, p2.GetX()));
    profile_points.push_back(vtkVector3d(p3.GetY(), 0.0, p3.GetX()));
    profile_points.push_back(vtkVector3d(p0.GetY(), 0.0, p0.GetX()));
    
    return profile_points;
}
}