#include "GeneratorCurve.h"

std::random_device GeneratorCurve::rd;

void GeneratorCurve::setDiapason(double min, double max)   
{
    if ((std::abs(max) + std::abs(min)) < 2 * eps)  // ���� �������� ��������� ������������ ������ ������ � ����,
        return;                                     // ������ �� ������
    udd = decltype(udd){ min, max };                // ������ ��������� ����
}

PCurve GeneratorCurve::circle()
{
    double radius{};
    while (radius < eps)            // ���������, ��� �� ������ ��� �� ������� ���������
        radius = std::abs(udd(rd)); // � > 0
    return std::make_shared<Circle3D>(Point3D{ udd(rd), udd(rd) }, radius);
}

PCurve GeneratorCurve::ellipse()
{ 
    double radius_x{};
    while (radius_x < eps)              // ���������, ��� �� ������ ������ ��� �� ������� ���������
        radius_x = std::abs(udd(rd));   // � > 0
    double radius_y{};
    while (radius_y < eps)              // ���������, ��� �� ������ ������ ��� �� ������� ���������
        radius_y = std::abs(udd(rd));   // � > 0
    return std::make_shared<Ellipse3D>(Point3D{ udd(rd), udd(rd) }, radius_x, radius_y);
}

PCurve GeneratorCurve::helix()
{ 
    double radius{};
    while (radius < eps)            // ���������, ��� �� ������ ��� �� ������� ���������
        radius = std::abs(udd(rd)); // � > 0
    double step{};
    while (std::abs(step) < eps)    // ���������, ��� �� ��� ��� �� ������� ���������
        step = udd(rd);
    return std::make_shared<Helix3D>(Point3D{ udd(rd), udd(rd), udd(rd) }, radius, step);
}

PCurve GeneratorCurve::randomCurve()
{   
    switch (usd(rd))
    {
    case ellipse_t:
        return ellipse();
    case helix_t:
        return helix();
    default:
        return circle();
    }
}
