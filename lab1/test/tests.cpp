#include <gtest/gtest.h>
#include <function.hpp>
#include <string>

TEST(DeleteVowelsTest, SimpleCase) {
    std::string result = text_processing::delete_vowels("Hello World");
    EXPECT_EQ(result, "Hll Wrld");
}

TEST(DeleteVowelsTest, OnlyVowels) {
    std::string result = text_processing::delete_vowels("aeiouAEIOU");
    EXPECT_EQ(result, "");
}

TEST(DeleteVowelsTest, NoVowels) {
    std::string result = text_processing::delete_vowels("bcdfghjklnm");
    EXPECT_EQ(result, "bcdfghjklnm");
}

TEST(DeleteVowelsTest, MixedCase) {
    std::string result = text_processing::delete_vowels("Programming");
    EXPECT_EQ(result, "Prgrmmng");
}

TEST(DeleteVowelsTest, EmptyString) {
    std::string result = text_processing::delete_vowels("");
    EXPECT_EQ(result, "");
}

TEST(DeleteVowelsTest, WithSpacesAndPunctuation) {
    std::string result = text_processing::delete_vowels("Hello, World!");
    EXPECT_EQ(result, "Hll, Wrld!");
}
