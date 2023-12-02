#pragma once
#include <random>
#include "Curves.h"

// генератор объектов - потомков Curve3D
class GeneratorCurve   
{
    // типы генерируемых объектов
    enum shape_t { circle_t, ellipse_t, helix_t };   
    //Объект генерации случайных чисел (из аппаратного обеспечения, где это доступно)
    static std::random_device rd;
    // генератор случайных вещественных чисел(ГСВЧ)
    std::uniform_real_distribution<double> udd{ -1, 1 }; 
    // генератор случайных типов объектов
    std::uniform_int_distribution<> usd{ circle_t, helix_t };   
public:
    //изменить диапазон
    void set_diapason(double min, double max);
    /* метод генерирует и размещает в динамической памяти объект класса Circle3D и возвращает умный указатель на базовый класс */
    PCurve circle();
    /* метод генерирует и размещает в динамической памяти объект класса Ellipse3D и возвращает умный указатель на базовый класс */
    PCurve ellipse();
    /* метод генерирует и размещает в динамической памяти объект класса Helix3D и возвращает умный указатель на базовый класс */
    PCurve helix();
    // метод генерирует случайную фигуру из доступного набора
    PCurve random_shape();
};
