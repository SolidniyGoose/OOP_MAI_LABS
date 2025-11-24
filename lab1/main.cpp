#include <iostream>
#include <function.hpp>

int main() {
    std::string input;
    std::string result;
    std::getline(std::cin, input);

    std::string result = text_processing::delete_vowels(input);
    
    std::cout << result << std::endl;

    return 0;
}
