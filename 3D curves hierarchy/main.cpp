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
    std::string greeting = "   Вас приветсвует программа \"3D curves hierarchy\"   ";
    std::cout << greeting << std::endl;
    printSeparator(std::cout,greeting.length());
    constexpr size_t sz = 10;       // размер первого массива
    std::vector<PCurve> shape_vec;  // массив указателей на объекты базового класса

    {
        GeneratorCurve s_gen;           // генератор
        s_gen.set_diapason(-15, 15);    // инициализируем диапазон
        for (size_t i{}; i < sz; ++i)
            shape_vec.emplace_back(s_gen.random_shape());   // заполняем массив
    }

    using PCircle = std::shared_ptr<Circle3D>;  // псевдоним типа - умный указатель на Circle3D

    std::vector<PCircle> circle_vec;    // массив указателей на Circle3D из первого контейнера

    double radius_sum{};    // сумма радиусов Circle3D

    for (auto& ps : shape_vec)
    {
        const std::type_info& ti{ typeid(*ps) };    // информация о типе объекта, на который указывает ps из первого контейнера

        std::cout << ti.name() << ' '   // выводим имя типа
            << ps->calcPoint(M_PI / 4) << ' '   // точку кривой, заданную параметром
            << ps->calcVector(M_PI / 4) << std::endl;   // вектор(первая производная - касательная) в предыдущей точке

        if (ti.hash_code() == typeid(Circle3D).hash_code()) // если текущий объект - указатель на Circle3D
        {
            circle_vec.emplace_back(std::dynamic_pointer_cast<Circle3D>(ps));   // приводим его к указателю на Circle3D
            radius_sum += circle_vec.back()->getRadius();  // вычисляем радиус
            std::cout << "к другому вектору -->\n";
        }
        std::cout << std::endl;
    }
    std::sort(circle_vec.begin(), circle_vec.end(), [](const auto& lh, const auto& rh)  // сортируем по радиусу
        {
            return lh->getRadius() < rh->getRadius();
        });

    for (auto& pc : circle_vec) // демонстрируем отсортированное
        std::cout << pc->getRadius() << std::endl;
    std::cout << "sum = " << radius_sum << std::endl;   // и сумму радиусов всех Circle3D
}