#define _USE_MATH_DEFINES
#include <GeneratorCurve.h>
#include <omp.h>
#include <string>

void printSeparator(std::ostream& os,unsigned int count,char separator = '=') {
    while (count)
    {
        --count;
        os << separator;
    }
    os << std::endl;
};

int main()
{
    system("chcp 1251 > nul");
    const std::string tab = "   ";
    std::string outText = "��� ����������� ��������� \"3D curves hierarchy\"";
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    outText = "1. ��������� ������������ ��������� ����� 3D��������������� ������, ����� ���:";
    std::cout << tab << outText << tab << std::endl << std::endl;
    std::cout << tab + tab << typeid(Circle3D) .name() << ", " 
                           << typeid(Ellipse3D).name() << ", " 
                           << typeid(Helix3D)  .name() << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    constexpr size_t sz = 40;       // ������ ������� �������
    outText = "2. ��������� ��������� "+ std::to_string(sz) +" ���������, ���������� ��������� �������, �� ���������� �����������";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    std::vector<PCurve> curve_vec;   // ������ ���������� �� ������� �������� ������ Curve3D
    {
        GeneratorCurve generator;
        generator.set_diapason(-20, 20);    // �������������� ��������
        for (size_t i{}; i < sz; ++i)
            curve_vec.emplace_back(generator.random_curve());   // ��������� ������
    }
    
    outText = "3. ������� ���������� ����� Point3D � ����������� Vector3D ���� ������ � ���������� ��� t=PI/4";
    std::cout << tab << outText << tab << std::endl << std::endl;
    int indx = 0;
    const double t = M_PI / 4;
    for (auto& pc : curve_vec)
    {
        std::cout << tab << "index-" << ++indx << "\t" << typeid(*pc).name() << "\t"
                  << pc->calcPoint(t) << tab << pc->calcVector(t) << std::endl << std::endl;
    }
    printSeparator(std::cout, outText.length() + 2 * tab.length());

    outText = "4. ��������� ������ ��������� ������ ������� �� ������� ����������.";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    // ������ ���������� �� Circle3D �� ������� ����������
    std::vector<PCircle> circle_vec;
    for (auto& pc : curve_vec)
      if (typeid(*pc).hash_code() == typeid(Circle3D).hash_code())        // ���� ������� ������ - ��������� �� Circle3D
        circle_vec.emplace_back(std::dynamic_pointer_cast<Circle3D>(pc)); // �������� ��� � ��������� �� Circle3D

    outText = "5. ��������� ������ ��������� � ������� ����������� �������� �����������.";
    std::cout << tab << outText << tab << std::endl;
    std::sort(circle_vec.begin(), circle_vec.end(), [](const auto& lh, const auto& rh)  // ��������� �� ������� (�� �����������)
        {
            return lh->getRadius() < rh->getRadius();
        });
    indx = 0;
    for (auto& pc : circle_vec)
      std::cout << tab << "index-" << ++indx << "\tr = " << pc->getRadius() << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    outText = "6. ��������� ����� ����� �������� ���� ������ �� ������ ����������.";
    std::cout << tab << outText << tab << std::endl;
    // ����� �������� Circle3D
    double radius_sum{};
    int i;
    //���������� ����� ����� �������� � �������������� ������������ ���������� (OpenMP)
#pragma omp parallel for reduction(+:radius_sum)
    for (i = 0; i < circle_vec.size(); i++)
        radius_sum += circle_vec[i]->getRadius();
    std::cout << tab << "sum = " << radius_sum << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    system("pause");
}