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
    std::string outText = "Вас приветсвует программа \"3D curves hierarchy\"";
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    outText = "1. Программа поддерживает несколько типов 3D–геометрических кривых, такие как:";
    std::cout << tab << outText << tab << std::endl << std::endl;
    std::cout << tab + tab << typeid(Circle3D) .name() << ", " 
                           << typeid(Ellipse3D).name() << ", " 
                           << typeid(Helix3D)  .name() << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    constexpr size_t sz = 40;       // размер первого массива
    outText = "2. Заполняем контейнер "+ std::to_string(sz) +" объектами, созданными случайным образом, со случайными параметрами";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    std::vector<PCurve> curve_vec;   // массив указателей на объекты базового класса Curve3D
    {
        GeneratorCurve generator;
        generator.set_diapason(-20, 20);    // инициализируем диапазон
        for (size_t i{}; i < sz; ++i)
            curve_vec.emplace_back(generator.random_curve());   // заполняем массив
    }
    
    outText = "3. Выводим координаты точек Point3D и производные Vector3D всех кривых в контейнере при t=PI/4";
    std::cout << tab << outText << tab << std::endl << std::endl;
    int indx = 0;
    const double t = M_PI / 4;
    for (auto& pc : curve_vec)
    {
        std::cout << tab << "index-" << ++indx << "\t" << typeid(*pc).name() << "\t"
                  << pc->calcPoint(t) << tab << pc->calcVector(t) << std::endl << std::endl;
    }
    printSeparator(std::cout, outText.length() + 2 * tab.length());

    outText = "4. Заполняем второй контейнер только кругами из первого контейнера.";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    // массив указателей на Circle3D из первого контейнера
    std::vector<PCircle> circle_vec;
    for (auto& pc : curve_vec)
      if (typeid(*pc).hash_code() == typeid(Circle3D).hash_code())        // если текущий объект - указатель на Circle3D
        circle_vec.emplace_back(std::dynamic_pointer_cast<Circle3D>(pc)); // приводим его к указателю на Circle3D

    outText = "5. Сортируем второй контейнер в порядке возрастания радиусов окружностей.";
    std::cout << tab << outText << tab << std::endl;
    std::sort(circle_vec.begin(), circle_vec.end(), [](const auto& lh, const auto& rh)  // сортируем по радиусу (по возрастанию)
        {
            return lh->getRadius() < rh->getRadius();
        });
    indx = 0;
    for (auto& pc : circle_vec)
      std::cout << tab << "index-" << ++indx << "\tr = " << pc->getRadius() << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    outText = "6. Вычисляем общую сумму радиусов всех кривых во втором контейнере.";
    std::cout << tab << outText << tab << std::endl;
    // сумма радиусов Circle3D
    double radius_sum{};
    int i;
    //вычисление общей суммы радиусов с использованием параллельных вычислений (OpenMP)
#pragma omp parallel for reduction(+:radius_sum)
    for (i = 0; i < circle_vec.size(); i++)
        radius_sum += circle_vec[i]->getRadius();
    std::cout << tab << "sum = " << radius_sum << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    system("pause");
}