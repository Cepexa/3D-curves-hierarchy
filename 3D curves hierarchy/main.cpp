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

int main(int argc, char** argv)
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

    // ������ ������� ������� �������� �� ���������� ������� (20 �� ���������, ���� �� ������� ���������)
    int sz = argc>1 ? std::abs(atoi(argv[1])) : 20;       
    outText = "2. ��������� ��������� "+ std::to_string(sz) +" ���������, ���������� ��������� �������, �� ���������� �����������";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    std::vector<PCurve> curveVec;   // ������ ���������� �� ������� �������� ������ Curve3D
    {
        GeneratorCurve generator;
        generator.setDiapason(-20, 20);    // �������������� ��������
        for (size_t i{}; i < sz; ++i)
            curveVec.emplace_back(generator.randomCurve());   // ��������� ������
    }
    
    outText = "3. ������� ���������� ����� Point3D � ����������� Vector3D ���� ������ � ���������� ��� t=PI/4";
    std::cout << tab << outText << tab << std::endl << std::endl;
    int indx = 0;
    const double t = M_PI / 4;
    for (auto& pc : curveVec)
    {
        std::cout << tab << "index-" << ++indx << "\t" << typeid(*pc).name() << "\t"
                  << pc->calcPoint(t) << tab << pc->calcVector(t) << std::endl << std::endl;
    }
    printSeparator(std::cout, outText.length() + 2 * tab.length());

    outText = "4. ��������� ������ ��������� ������ ������� �� ������� ����������.";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    // ������ ���������� �� Circle3D �� ������� ����������
    std::vector<PCircle> circleVec;
    for (auto& pc : curveVec)
      if (typeid(*pc).hash_code() == typeid(Circle3D).hash_code())        // ���� ������� ������ - ��������� �� Circle3D
        circleVec.emplace_back(std::dynamic_pointer_cast<Circle3D>(pc)); // �������� ��� � ��������� �� Circle3D

    outText = "5. ��������� ������ ��������� � ������� ����������� �������� �����������.";
    std::cout << tab << outText << tab << std::endl;
    std::sort(circleVec.begin(), circleVec.end(), [](const auto& lh, const auto& rh)  // ��������� �� ������� (�� �����������)
        {
            return lh->getRadius() < rh->getRadius();
        });
    indx = 0;
    for (auto& pc : circleVec)
      std::cout << tab << "index-" << ++indx << "\tr = " << pc->getRadius() << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    outText = "6. ��������� ����� ����� �������� ���� ������ �� ������ ����������.";
    std::cout << tab << outText << tab << std::endl;
    // ����� �������� Circle3D
    double radiusSum{};
    int i;
    //���������� ����� ����� �������� � �������������� ������������ ���������� (OpenMP)
#pragma omp parallel for reduction(+:radiusSum)
    for (i = 0; i < static_cast<int>(circleVec.size()); i++)
        radiusSum += circleVec[i]->getRadius();
    std::cout << tab << "sum = " << radiusSum << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    system("pause");
}