// main.cpp
#include <iostream>
#include <memory>
#include <iomanip>
#include <limits>

#include "point.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "array.hpp"

int main() {
    std::cout << std::fixed << std::setprecision(3);
    
    //массив с умными указателями
    Array<std::shared_ptr<Figure<double>>> figures;
    
    while (true) {
        std::cout << "\n=== Меню ===\n"
                  << "1. Добавить фигуру\n"
                  << "2. Показать все фигуры\n"
                  << "3. Общая площадь\n"
                  << "0. Выход\n> ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: { // Добавить фигуру
                std::cout << "\nТип фигуры:\n"
                          << "1. Квадрат\n"
                          << "2. Прямоугольник\n"
                          << "3. Трапеция\n> ";
                
                int type;
                std::cin >> type;
                
                if (type == 1) { // квадрат
                    double x, y, side;
                    std::cout << "Центр (x y) и сторона: ";
                    std::cin >> x >> y >> side;
                    
                    if (std::cin && side > 0) {
                        Point<double> center{x, y};
                        auto square = std::shared_ptr<Figure<double>>(new Square<double>(center, side));
                        figures.PushBack(square);
                        std::cout << "Квадрат добавлен.\n";
                    }
                } 
                else if (type == 2) { // прямоугольник
                    double x, y, width, height;
                    std::cout << "Центр (x y), ширина и высота: ";
                    std::cin >> x >> y >> width >> height;
                    
                    if (std::cin && width > 0 && height > 0) {
                        Point<double> center{x, y};
                        auto rect = std::shared_ptr<Figure<double>>(new Rectangle<double>(center, width, height));
                        figures.PushBack(rect);
                        std::cout << "Прямоугольник добавлен.\n";
                    }
                }
                else if (type == 3) { // трапеция
                    std::cout << "4 вершины (x1 y1 x2 y2 x3 y3 x4 y4): ";
                    double x1, y1, x2, y2, x3, y3, x4, y4;
                    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
                    
                    if (std::cin) {
                        Point<double> a{x1, y1}, b{x2, y2}, c{x3, y3}, d{x4, y4};
                        auto trap = std::shared_ptr<Figure<double>>(new Trapezoid<double>(a, b, c, d));
                        figures.PushBack(trap);
                        std::cout << "Трапеция добавлена.\n";
                    }
                }
                
                break;
            }
            
            case 2: { //все фигуры
                if (figures.Empty()) {
                    std::cout << "Нет фигур.\n";
                    break;
                }
                
                double total = 0.0;
                for (std::size_t i = 0; i < figures.Size(); ++i) {
                    std::cout << "\nФигура " << i << ": ";
                    figures[i]->Print(std::cout);
                    std::cout << "\nЦентр: " << figures[i]->Center() 
                              << " Площадь: " << figures[i]->Area() << "\n";
                    total += figures[i]->Area();
                }
                std::cout << "\nОбщая площадь: " << total << "\n";
                break;
            }
            
            case 3: { // Общая площадь
                double total = 0.0;
                for (std::size_t i = 0; i < figures.Size(); ++i) {
                    total += figures[i]->Area();
                }
                std::cout << "Общая площадь: " << total << "\n";
                break;
            }
            
            default:
                std::cout << "Неверный выбор\n";
                break;
        }
    }
    
    std::cout << "\n=== Демонстрация Array ===\n";
    
    std::cout << "1. Array<shared_ptr<Figure<double>>>:\n";
    for (std::size_t i = 0; i < figures.Size(); ++i) {
        std::cout << "  Фигура " << i << " площадь: " << figures[i]->Area() << "\n";
    }
    
    std::cout << "\n2. Array<Square<double>>:\n";
    Array<Square<double>> squares;
    squares.PushBack(Square<double>(Point<double>{0, 0}, 2.0));
    squares.PushBack(Square<double>(Point<double>{5, 5}, 3.0));
    
    for (std::size_t i = 0; i < squares.Size(); ++i) {
        std::cout << "  Квадрат " << i << " площадь: " << squares[i].Area() << "\n";
    }
    
    std::cout << "\n3. Array<Figure<double>*> (демонстрация):\n";
    Array<Figure<double>*> ptrArray;
    ptrArray.PushBack(new Square<double>(Point<double>{1, 1}, 1.0));
    ptrArray.PushBack(new Rectangle<double>(Point<double>{2, 2}, 2.0, 3.0));
    
    for (std::size_t i = 0; i < ptrArray.Size(); ++i) {
        std::cout << "  Фигура " << i << " площадь: " << ptrArray[i]->Area() << "\n";
    }
    
    for (std::size_t i = 0; i < ptrArray.Size(); ++i) {
        delete ptrArray[i];
    }
    
    return 0;
}