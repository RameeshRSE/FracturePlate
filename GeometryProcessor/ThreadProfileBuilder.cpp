#include "ThreadProfileBuilder.hpp"
#include <cmath>
#include <iostream>
#include <vtkVector.h>
#include "../GeometricAlgo/CoreMath.hpp"


namespace Algo {
using namespace CoreMath;

std::vector<vtkVector3d> CreateVShapeThreadProfile(double major_dia, double minor_dia, double pitch)
{
    std::vector<vtkVector3d> profile_points;
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

std::vector<vtkVector3d> CreateButtressThreadProfile(double major_dia, double minor_dia, double pitch)
{
    std::vector<vtkVector3d> profile_points;
    const double pby6 = pitch/6.0;
    Line2D lVertical(1.0, 0.0, 0.0);
    Line2D lMajor(0.0, 1, major_dia);
    Line2D lMinor(0.0, 1, minor_dia);
    auto p1 = CalcLineIntersection(lVertical, lMinor);
    auto p2 =  CalcLineIntersection(lVertical, lMajor);
    auto p3 = vtkVector2d(p2.GetX() + pby6 , p2.GetY() );
    double slop = tan((180.0 - 52.0)  * DtoR);
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
}