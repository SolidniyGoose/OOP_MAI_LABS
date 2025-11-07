#include <gtest/gtest.h>
#include "octal.hpp"
#include "array.hpp"
#include <stdexcept>

using namespace octal;

TEST(ArrayTest, DefaultConstructor) {
    Array::Array arr;
    EXPECT_EQ(arr.Size(), 0);
    EXPECT_TRUE(arr.IsEmpty());
    EXPECT_EQ(arr.Capacity(), 0);
}

TEST(ArrayTest, ParameterizedConstructor) {
    Array::Array arr(5, 'A');
    EXPECT_EQ(arr.Size(), 5);
    EXPECT_EQ(arr.Capacity(), 5);
    EXPECT_EQ(arr.at(0), 'A');
    EXPECT_EQ(arr.at(4), 'A');
}

TEST(ArrayTest, InitializerListConstructor) {
    Array::Array arr{'1', '2', '3'};
    EXPECT_EQ(arr.Size(), 3);
    EXPECT_EQ(arr.at(0), '1');
    EXPECT_EQ(arr.at(1), '2');
    EXPECT_EQ(arr.at(2), '3');
}

TEST(OctalTest, DefaultConstructor) {
    octal::Octal oct;
    EXPECT_TRUE(oct.isZero());
    EXPECT_EQ(oct.ShowNumber(), "0");
    EXPECT_EQ(oct.size(), 1);
}

TEST(OctalTest, SizeConstructor) {
    octal::Octal oct(3, 5);
    EXPECT_EQ(oct.ShowNumber(), "555");
    EXPECT_EQ(oct.size(), 3);
}

TEST(OctalTest, StringConstructor) {
    octal::Octal oct("1234");
    EXPECT_EQ(oct.ShowNumber(), "1234");
    EXPECT_EQ(oct.size(), 4);
}

TEST(OctalTest, StringConstructorWithLeadingZeros) {
    octal::Octal oct("0012");
    EXPECT_EQ(oct.ShowNumber(), "12");
    EXPECT_EQ(oct.size(), 2);
}

TEST(OctalTest, CopyAndMoveConstructors) {
    octal::Octal oct1("1234");
    octal::Octal oct2(oct1);
    EXPECT_EQ(oct2.ShowNumber(), "1234");
    
    octal::Octal oct3(std::move(oct1));
    EXPECT_EQ(oct3.ShowNumber(), "1234");
    EXPECT_TRUE(oct1.isZero());
}

TEST(OctalTest, AdditionOperations) {
    octal::Octal oct1("123");
    octal::Octal oct2("456");
    octal::Octal result = octal::Octal::Add(oct1, oct2);
    EXPECT_EQ(result.ShowNumber(), "601");
    
    octal::Octal zero;
    octal::Octal sum_with_zero = octal::Octal::Add(oct1, zero);
    EXPECT_EQ(sum_with_zero.ShowNumber(), "123");
}

TEST(OctalTest, SubtractionOperations) {
    octal::Octal oct1("601");
    octal::Octal oct2("456");
    octal::Octal result = octal::Octal::Sub(oct1, oct2);
    EXPECT_EQ(result.ShowNumber(), "123");
    
    octal::Octal zero;
    octal::Octal diff_with_zero = octal::Octal::Sub(oct1, zero);
    EXPECT_EQ(diff_with_zero.ShowNumber(), "601");
}

TEST(OctalTest, SubtractionUnderflow) {
    octal::Octal oct1("123");
    octal::Octal oct2("456");
    EXPECT_THROW(octal::Octal::Sub(oct1, oct2), std::underflow_error);
}

TEST(OctalTest, MultiplicationOperations) {
    octal::Octal oct1("12");
    octal::Octal oct2("3");
    octal::Octal result = octal::Octal::Multiply(oct1, oct2);
    EXPECT_EQ(result.ShowNumber(), "36");
    
    octal::Octal zero;
    octal::Octal product_with_zero = octal::Octal::Multiply(oct1, zero);
    EXPECT_TRUE(product_with_zero.isZero());
}

TEST(OctalTest, ComparisonOperations) {
    octal::Octal oct1("123");
    octal::Octal oct2("456");
    octal::Octal oct3("123");
    
    EXPECT_TRUE(oct1.LessThen(oct2));
    EXPECT_TRUE(oct2.GreaterThen(oct1));
    EXPECT_TRUE(oct1.Equal(oct3));
    EXPECT_FALSE(oct1.Equal(oct2));
}

TEST(OctalTest, DigitAccess) {
    octal::Octal oct("1234");
    EXPECT_EQ(oct.digitAt(0), 4);
    EXPECT_EQ(oct.digitAt(1), 3);
    EXPECT_EQ(oct.digitAt(2), 2);
    EXPECT_EQ(oct.digitAt(3), 1);
    EXPECT_EQ(oct.digitAt(10), 0);
}

TEST(OctalTest, LargeNumbers) {
    octal::Octal oct1("7777777");
    octal::Octal oct2("1");
    octal::Octal result = octal::Octal::Add(oct1, oct2);
    EXPECT_EQ(result.ShowNumber(), "10000000");
}

TEST(OctalTest, InvalidDigits) {
    EXPECT_THROW(octal::Octal oct(3, 8), std::invalid_argument);
    EXPECT_THROW(octal::Octal oct("128"), std::invalid_argument);
    EXPECT_THROW((octal::Octal{1, 2, 8}), std::invalid_argument);
}

TEST(OctalTest, CopyMethod) {
    octal::Octal oct1("1234");
    octal::Octal oct2;
    oct2.Copy(oct1);
    EXPECT_EQ(oct2.ShowNumber(), "1234");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}