#pragma once
#include <math.h>
#include <iostream>
constexpr double eps = 1e-6;

struct Point3D { double x{}, y{}, z{}; };
struct Vector3D { double x{}, y{}, z{}; };
std::ostream& operator<<(std::ostream& os, const Point3D& p);
std::ostream& operator<<(std::ostream& os, const Vector3D& v);

//Aбстрактный класс
class Curve3D  
{
protected:
    Point3D center{};
    Curve3D() = default;
    Curve3D(const Point3D& c) : center{ c } {}
public:
    virtual ~Curve3D() {}
    virtual Point3D calcPoint(double t) const = 0;    
    virtual Vector3D calcVector(double t) const = 0;
};

class Circle3D : public Curve3D
{
    double radius{};
public:
    Circle3D() = default;
    Circle3D(const Point3D& c, double rad) : Curve3D(c), radius{ rad } {}
    ~Circle3D() {}
    double getRadius() const;
    Point3D  calcPoint(double t) const override;
    Vector3D calcVector(double t) const override;
};

class Ellipse3D : public Curve3D
{
    double radius_x{};
    double radius_y{};
public:
    Ellipse3D() = default;
    Ellipse3D(const Point3D& c, double radius_x, double radius_y) :Curve3D(c), radius_x{ radius_x }, radius_y{ radius_y } {}
    ~Ellipse3D() {}
    Point3D calcPoint(double t) const override;
    Vector3D calcVector(double t) const override;
};

class Helix3D : public Curve3D
{
    double radius{};
    double step{};
public:
    Helix3D() = default;
    Helix3D(const Point3D& c, double rad, double step_z) : Curve3D(c), radius{ rad }, step{ step_z } {}
    ~Helix3D() {}
    Point3D  calcPoint(double t) const override;
    Vector3D calcVector(double t) const override;
};

// псевдоним типа - умный указатель на Point3D
using PPoint = std::shared_ptr<Point3D>;
// псевдоним типа - умный указатель на Vector3D
using PVector = std::shared_ptr<Vector3D>;
// псевдоним типа - умный указатель на базовый класс Curve3D
using PCurve = std::shared_ptr<Curve3D>;
// псевдоним типа - умный указатель на Circle3D
using PCircle = std::shared_ptr<Circle3D>;
// псевдоним типа - умный указатель на Ellipse3D
using PEllipse = std::shared_ptr<Ellipse3D>;
// псевдоним типа - умный указатель на Helix3D
using PHelix = std::shared_ptr<Helix3D>;


