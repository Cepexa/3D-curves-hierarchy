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
    std::string greeting = "   ��� ����������� ��������� \"3D curves hierarchy\"   ";
    std::cout << greeting << std::endl;
    printSeparator(std::cout,greeting.length());
    constexpr size_t sz = 10;       // ������ ������� �������
    std::vector<PCurve> shape_vec;  // ������ ���������� �� ������� �������� ������

    {
        GeneratorCurve s_gen;           // ���������
        s_gen.set_diapason(-15, 15);    // �������������� ��������
        for (size_t i{}; i < sz; ++i)
            shape_vec.emplace_back(s_gen.random_shape());   // ��������� ������
    }

    using PCircle = std::shared_ptr<Circle3D>;  // ��������� ���� - ����� ��������� �� Circle3D

    std::vector<PCircle> circle_vec;    // ������ ���������� �� Circle3D �� ������� ����������

    double radius_sum{};    // ����� �������� Circle3D

    for (auto& ps : shape_vec)
    {
        const std::type_info& ti{ typeid(*ps) };    // ���������� � ���� �������, �� ������� ��������� ps �� ������� ����������

        std::cout << ti.name() << ' '   // ������� ��� ����
            << ps->calcPoint(M_PI / 4) << ' '   // ����� ������, �������� ����������
            << ps->calcVector(M_PI / 4) << std::endl;   // ������(������ ����������� - �����������) � ���������� �����

        if (ti.hash_code() == typeid(Circle3D).hash_code()) // ���� ������� ������ - ��������� �� Circle3D
        {
            circle_vec.emplace_back(std::dynamic_pointer_cast<Circle3D>(ps));   // �������� ��� � ��������� �� Circle3D
            radius_sum += circle_vec.back()->getRadius();  // ��������� ������
            std::cout << "� ������� ������� -->\n";
        }
        std::cout << std::endl;
    }
    std::sort(circle_vec.begin(), circle_vec.end(), [](const auto& lh, const auto& rh)  // ��������� �� �������
        {
            return lh->getRadius() < rh->getRadius();
        });

    for (auto& pc : circle_vec) // ������������� ���������������
        std::cout << pc->getRadius() << std::endl;
    std::cout << "sum = " << radius_sum << std::endl;   // � ����� �������� ���� Circle3D
}