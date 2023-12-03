#include "Curves.h"

std::ostream& operator<<(std::ostream& os, const Point3D& p)
{  
    return os << "Point3D{ " << p.x << ", " << p.y << ", " << p.z << " }";
}
std::ostream& operator<<(std::ostream& os, const Vector3D& v)
{   
    return os << "Vector3D{ " << v.x << ", " << v.y << ", " << v.z << " }";
}

double Circle3D::getRadius() const
{
    return radius;
}
Point3D Circle3D::calcPoint(double t) const
{
    return Point3D{ radius * std::cos(t) + center.x, radius * std::sin(t) + center.y, center.z };
}
Vector3D Circle3D::calcVector(double t) const
{
    return Vector3D{ -1 * radius * std::sin(t), radius * std::cos(t) };
}
Point3D Ellipse3D::calcPoint(double t) const
{
    return Point3D{ radius_x * std::cos(t) + center.x,radius_y * std::sin(t) + center.y,center.z };
}
Vector3D Ellipse3D::calcVector(double t) const
{
    return Vector3D{ -1 * radius_x * std::sin(t), radius_y * std::cos(t) };
}
Point3D Helix3D::calcPoint(double t) const
{
    return Point3D{ radius * t * std::cos(t) + center.x,radius * t * std::sin(t) + center.y,step * t + center.z };
}
Vector3D Helix3D::calcVector(double t) const
{
    return Vector3D{ radius * (std::cos(t) - t * std::sin(t)),radius * (std::sin(t) + t * std::cos(t)), step };
}


