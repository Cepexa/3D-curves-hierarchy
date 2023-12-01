#pragma once
#include <random>
#include "Curves.h"

// ��������� ���� - ����� ��������� �� ������� �����
using PCurve = std::shared_ptr<Curve3D>;
// ��������� ���� - ����� ��������� �� Circle3D
using PCircle = std::shared_ptr<Circle3D>;  
// ��������� ���� - ����� ��������� �� Ellipse3D
using PEllipse = std::shared_ptr<Ellipse3D>;
// ��������� ���� - ����� ��������� �� Helix3D
using PHelix = std::shared_ptr<Helix3D>;

// ��������� �������� - �������� Curve3D
class GeneratorCurve   
{
    // ���� ������������ ��������
    enum shape_t { circle_t, ellipse_t, helix_t };   
    //������ ��������� ��������� ����� (�� ����������� �����������, ��� ��� ��������)
    static std::random_device rd;
    // ��������� ��������� ������������ �����(����)
    std::uniform_real_distribution<double> udd{ -1, 1 }; 
    // ��������� ��������� ����� ��������
    std::uniform_int_distribution<> usd{ circle_t, helix_t };   
public:
    //�������� ��������
    void set_diapason(double min, double max);
    /* ����� ���������� � ��������� � ������������ ������ ������ ������ Circle3D � ���������� ����� ��������� �� ������� ����� */
    PCurve circle();
    /* ����� ���������� � ��������� � ������������ ������ ������ ������ Ellipse3D � ���������� ����� ��������� �� ������� ����� */
    PCurve ellipse();
    /* ����� ���������� � ��������� � ������������ ������ ������ ������ Helix3D � ���������� ����� ��������� �� ������� ����� */
    PCurve helix();
    // ����� ���������� ��������� ������ �� ���������� ������
    PCurve random_shape();
};
