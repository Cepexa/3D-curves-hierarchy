#define _USE_MATH_DEFINES
#include "GeneratorCurve.h"
#include "omp.h"

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
    printSeparator(std::cout, outText.length()+2* tab.length());
    Circle3D  PCircle3D;
    Ellipse3D PEllipse3D;
    Helix3D   PHelix3D;
    outText = "1. ��������� ������������ ��������� ����� 3D��������������� ������, ����� ���:";
    std::cout << tab << outText << tab << std::endl << std::endl;
    std::cout << tab+tab << typeid(PCircle3D).name() << ", " << typeid(PEllipse3D).name() << ", " << typeid(PHelix3D).name() << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    constexpr size_t sz = 20;       // ������ ������� �������
    std::vector<PCurve> shape_vec;  // ������ ���������� �� ������� �������� ������
    {
        GeneratorCurve generator;
        generator.set_diapason(-20, 20);    // �������������� ��������
        for (size_t i{}; i < sz; ++i)
            shape_vec.emplace_back(generator.random_shape());   // ��������� ������
    }
    outText = "2. ��������� ��������� ���������, ���������� ��������� �������, �� ���������� �����������";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    outText = "3. ������� ���������� ����� Point3D � ����������� Vector3D ���� ������ � ���������� ��� t=PI/4";
    std::cout << tab << outText << tab << std::endl << std::endl;
    // ������ ���������� �� Circle3D �� ������� ����������
    std::vector<PCircle> circle_vec;    
    // ����� �������� Circle3D
    double radius_sum{};    
    int indx = 0;
    const double t = M_PI / 4;
    for (auto& ps : shape_vec)
    {
        const std::type_info& ti{ typeid(*ps) };    // ���������� � ���� �������, �� ������� ��������� ps �� ������� ����������
        std::cout << tab << "index-"<< ++indx << "\t" << ti.name() << "\t"
                  << ps->calcPoint(t) <<  "\t"
                  << ps->calcVector(t) << std::endl;
        if (ti.hash_code() == typeid(Circle3D).hash_code()) // ���� ������� ������ - ��������� �� Circle3D
        {
            circle_vec.emplace_back(std::dynamic_pointer_cast<Circle3D>(ps));   // �������� ��� � ��������� �� Circle3D
            radius_sum += circle_vec.back()->getRadius();                       // ��������� ������
        }
        std::cout << std::endl;
    }
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    outText = "4. ��������� ������ ��������� ������ ������� �� ������� ����������.";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    outText = "5. ��������� ������ ��������� � ������� ����������� �������� �����������.";
    std::cout << tab << outText << tab << std::endl;

    std::sort(circle_vec.begin(), circle_vec.end(), [](const auto& lh, const auto& rh)  // ��������� �� �������
        {
            return lh->getRadius() < rh->getRadius();
        });
    indx = 0;
    for (auto& pc : circle_vec)
        std::cout << tab << "index-" << ++indx << "\tr = " << pc->getRadius() << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    outText = "6. ��������� ����� ����� �������� ���� ������ �� ������ ����������.";
    std::cout << tab << outText << tab << std::endl;
    std::cout << tab << "sum = " << radius_sum << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
}