#include <iostream>
#include <string>
#include "octal.hpp"

int main() {
    std::cout << "Enter octal number to see it: ";
    std::string input;
    std::cin >> input;
    
    try {
        octal::Octal number(input);
        std::cout << number.ShowNumber() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid octal number" << std::endl;
    }
    
    return 0;
}