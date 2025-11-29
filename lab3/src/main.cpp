#include <iostream>
#include "FigureArray.hpp"
#include "Trapezoid.hpp"
#include "Rhomb.hpp"
#include "Pentagon.hpp"

void printFiguresInfo(FigureArray& figures) {
    double totalArea = 0.0;
    
    for (size_t i = 0; i < figures.Size(); ++i) {
        if (figures[i] != nullptr) {
            std::cout << "Figure " << i << ":" << std::endl;
            std::cout << "  Type: ";
            if (dynamic_cast<Trapezoid*>(figures[i])) std::cout << "Trapezoid";
            else if (dynamic_cast<Rhomb*>(figures[i])) std::cout << "Rhomb";
            else if (dynamic_cast<Pentagon*>(figures[i])) std::cout << "Pentagon";
            std::cout << std::endl;
            
            std::cout << "  Points: " << *figures[i] << std::endl;
            std::cout << "  Center: " << figures[i]->Center() << std::endl;
            std::cout << "  Area: " << figures[i]->Area() << std::endl;
            
            totalArea += figures[i]->Area();
        }
    }
    
    std::cout << "Total area of all figures: " << totalArea << std::endl;
}

int main() {
    FigureArray figures;
    
    std::cout << "Creating figures" << std::endl;
    
    figures.PushBack(new Trapezoid(Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)));
    
    figures.PushBack(new Rhomb(Point(0, 0), Point(2, 3), Point(4, 0), Point(2, -3)));
    
    figures.PushBack(new Pentagon(Point(0, 0), Point(2, 1), Point(3, 3), Point(1, 4), Point(-1, 2)));
    
    printFiguresInfo(figures);
    
    figures.Erase(1);
    
    printFiguresInfo(figures);
    
    std::cout << "\nComparison" << std::endl;
    if (figures.Size() >= 2) {
        bool areEqual = (*figures[0] == *figures[1]);
        std::cout << "Figure 0 == Figure 1: " << (areEqual ? "true" : "false") << std::endl;
    }
    
    std::cout << "\nCopy" << std::endl;
    Figure* copiedFigure = figures[0]->Copy();
    std::cout << "Copied figure: " << *copiedFigure << std::endl;
    std::cout << "Original == Copied: " << (*figures[0] == *copiedFigure ? "true" : "false") << std::endl;
    delete copiedFigure;
    
    return 0;
}