#include <function.hpp>

namespace text_processing {
    std::string delete_vowels(const std::string& input){
        const char vowels[] = {'a','e','u','i','o','A','E','U','I','O'};
        std::string new_str;
        for (char letter : input){
            bool isVowel = false;
            for (char vowel : vowels){
                if (letter == vowel){
                    isVowel = true;
                    break;
                }
            }
            if (!isVowel) {
                new_str += letter;
            }
        }
        return new_str;
    }
}
