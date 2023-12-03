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

    // размер первого массива получаем из аргументов команды (20 по умолчанию, если не указаны аргументы)
    int sz = argc>1 ? std::abs(atoi(argv[1])) : 20;       
    outText = "2. Заполняем контейнер "+ std::to_string(sz) +" объектами, созданными случайным образом, со случайными параметрами";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    std::vector<PCurve> curveVec;   // массив указателей на объекты базового класса Curve3D
    {
        GeneratorCurve generator;
        generator.setDiapason(-20, 20);    // инициализируем диапазон
        for (size_t i{}; i < sz; ++i)
            curveVec.emplace_back(generator.randomCurve());   // заполняем массив
    }
    
    outText = "3. Выводим координаты точек Point3D и производные Vector3D всех кривых в контейнере при t=PI/4";
    std::cout << tab << outText << tab << std::endl << std::endl;
    int indx = 0;
    const double t = M_PI / 4;
    for (auto& pc : curveVec)
    {
        std::cout << tab << "index-" << ++indx << "\t" << typeid(*pc).name() << "\t"
                  << pc->calcPoint(t) << tab << pc->calcVector(t) << std::endl << std::endl;
    }
    printSeparator(std::cout, outText.length() + 2 * tab.length());

    outText = "4. Заполняем второй контейнер только кругами из первого контейнера.";
    std::cout << tab << outText << tab << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    // массив указателей на Circle3D из первого контейнера
    std::vector<PCircle> circleVec;
    for (auto& pc : curveVec)
      if (typeid(*pc).hash_code() == typeid(Circle3D).hash_code())        // если текущий объект - указатель на Circle3D
        circleVec.emplace_back(std::dynamic_pointer_cast<Circle3D>(pc)); // приводим его к указателю на Circle3D

    outText = "5. Сортируем второй контейнер в порядке возрастания радиусов окружностей.";
    std::cout << tab << outText << tab << std::endl;
    std::sort(circleVec.begin(), circleVec.end(), [](const auto& lh, const auto& rh)  // сортируем по радиусу (по возрастанию)
        {
            return lh->getRadius() < rh->getRadius();
        });
    indx = 0;
    for (auto& pc : circleVec)
      std::cout << tab << "index-" << ++indx << "\tr = " << pc->getRadius() << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    outText = "6. Вычисляем общую сумму радиусов всех кривых во втором контейнере.";
    std::cout << tab << outText << tab << std::endl;
    // сумма радиусов Circle3D
    double radiusSum{};
    int i;
    //вычисление общей суммы радиусов с использованием параллельных вычислений (OpenMP)
#pragma omp parallel for reduction(+:radiusSum)
    for (i = 0; i < static_cast<int>(circleVec.size()); i++)
        radiusSum += circleVec[i]->getRadius();
    std::cout << tab << "sum = " << radiusSum << std::endl;
    printSeparator(std::cout, outText.length() + 2 * tab.length());
    
    system("pause");
}