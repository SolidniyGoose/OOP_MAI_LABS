#include <gtest/gtest.h>
#include <memory>
#include <sstream>

#include "point.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "array.hpp"

TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(1.5, 2.5);
    EXPECT_DOUBLE_EQ(p.x, 1.5);
    EXPECT_DOUBLE_EQ(p.y, 2.5);
}

TEST(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(3.0, 4.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, InequalityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(3.0, 4.0);
    
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 != p1);
}

TEST(PointTest, InputOutput) {
    Point<double> p;
    std::stringstream ss("3.14 2.71");
    ss >> p;
    
    EXPECT_DOUBLE_EQ(p.x, 3.14);
    EXPECT_DOUBLE_EQ(p.y, 2.71);
    
    std::stringstream out;
    out << p;
    EXPECT_EQ(out.str(), "(3.14, 2.71)");
}

TEST(SquareTest, DefaultConstructor) {
    Square<double> s;
    EXPECT_EQ(s.VerticesCount(), 4);
    EXPECT_GT(s.Area(), 0.0);
}

TEST(SquareTest, ParameterizedConstructor) {
    Point<double> center(1.0, 2.0);
    Square<double> s(center, 4.0);
    
    EXPECT_EQ(s.VerticesCount(), 4);
    EXPECT_DOUBLE_EQ(s.Area(), 16.0);
    
    Point<double> c = s.Center();
    EXPECT_DOUBLE_EQ(c.x, 1.0);
    EXPECT_DOUBLE_EQ(c.y, 2.0);
}

TEST(SquareTest, AreaCalculation) {
    Point<double> center(0.0, 0.0);
    Square<double> s1(center, 2.0);
    EXPECT_DOUBLE_EQ(s1.Area(), 4.0);
    
    Square<double> s2(center, 5.0);
    EXPECT_DOUBLE_EQ(s2.Area(), 25.0);
}

TEST(SquareTest, Clone) {
    Point<double> center(1.0, 1.0);
    Square<double> s(center, 3.0);
    auto cloned = s.Clone();
    
    EXPECT_NE(cloned.get(), &s);
    EXPECT_DOUBLE_EQ(cloned->Area(), s.Area());
    EXPECT_TRUE(s.Center() == cloned->Center());
}

TEST(SquareTest, InputOutput) {
    Square<double> s;
    std::stringstream ss("2.0 3.0 4.0");
    
    ss >> s;
    
    EXPECT_DOUBLE_EQ(s.Area(), 16.0);
    
    std::stringstream out;
    out << s;
    EXPECT_TRUE(out.str().find("Square:") != std::string::npos);
}

TEST(RectangleTest, DefaultConstructor) {
    Rectangle<double> r;
    EXPECT_EQ(r.VerticesCount(), 4);
    EXPECT_GT(r.Area(), 0.0);
}

TEST(RectangleTest, ParameterizedConstructor) {
    Point<double> center(1.0, 2.0);
    Rectangle<double> r(center, 4.0, 3.0);
    
    EXPECT_EQ(r.VerticesCount(), 4);
    EXPECT_DOUBLE_EQ(r.Area(), 12.0);
    
    Point<double> c = r.Center();
    EXPECT_DOUBLE_EQ(c.x, 1.0);
    EXPECT_DOUBLE_EQ(c.y, 2.0);
}

TEST(RectangleTest, AreaCalculation) {
    Point<double> center(0.0, 0.0);
    Rectangle<double> r1(center, 4.0, 3.0);
    EXPECT_DOUBLE_EQ(r1.Area(), 12.0);
    
    Rectangle<double> r2(center, 5.0, 2.5);
    EXPECT_DOUBLE_EQ(r2.Area(), 12.5);
}

TEST(RectangleTest, Clone) {
    Point<double> center(1.0, 1.0);
    Rectangle<double> r(center, 4.0, 3.0);
    auto cloned = r.Clone();
    
    EXPECT_NE(cloned.get(), &r);
    EXPECT_DOUBLE_EQ(cloned->Area(), r.Area());
    EXPECT_TRUE(r.Center() == cloned->Center());
}

TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid<double> t;
    EXPECT_EQ(t.VerticesCount(), 4);
    EXPECT_GT(t.Area(), 0.0);
}

TEST(TrapezoidTest, ParameterizedConstructor) {
    Point<double> a(0.0, 0.0);
    Point<double> b(4.0, 0.0);
    Point<double> c(3.0, 2.0);
    Point<double> d(1.0, 2.0);
    
    Trapezoid<double> t(a, b, c, d);
    
    EXPECT_EQ(t.VerticesCount(), 4);
    EXPECT_DOUBLE_EQ(t.Area(), 6.0);
}

TEST(TrapezoidTest, Clone) {
    Point<double> a(0.0, 0.0);
    Point<double> b(4.0, 0.0);
    Point<double> c(3.0, 2.0);
    Point<double> d(1.0, 2.0);
    
    Trapezoid<double> t(a, b, c, d);
    auto cloned = t.Clone();
    
    EXPECT_NE(cloned.get(), &t);
    EXPECT_DOUBLE_EQ(cloned->Area(), t.Area());
}

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.Size(), 0);
    EXPECT_EQ(arr.Capacity(), 0);
    EXPECT_TRUE(arr.Empty());
}

TEST(ArrayTest, ConstructorWithSize) {
    Array<int> arr(5);
    EXPECT_EQ(arr.Size(), 5);
    EXPECT_EQ(arr.Capacity(), 5);
    EXPECT_FALSE(arr.Empty());
}

TEST(ArrayTest, PushBackAndAccess) {
    Array<int> arr;
    arr.PushBack(10);
    arr.PushBack(20);
    arr.PushBack(30);
    
    EXPECT_EQ(arr.Size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArrayTest, AtMethod) {
    Array<double> arr;
    arr.PushBack(1.1);
    arr.PushBack(2.2);
    
    EXPECT_DOUBLE_EQ(arr.At(0), 1.1);
    EXPECT_DOUBLE_EQ(arr.At(1), 2.2);
    
    EXPECT_THROW(arr.At(5), std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1;
    arr1.PushBack(1);
    arr1.PushBack(2);
    
    Array<int> arr2 = arr1;
    
    EXPECT_EQ(arr2.Size(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    
    arr1[0] = 100;
    EXPECT_EQ(arr2[0], 1);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1;
    arr1.PushBack(1);
    arr1.PushBack(2);
    
    Array<int> arr2 = std::move(arr1);
    
    EXPECT_EQ(arr2.Size(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr1.Size(), 0);
}

TEST(ArrayTest, Erase) {
    Array<int> arr;
    arr.PushBack(1);
    arr.PushBack(2);
    arr.PushBack(3);
    
    arr.Erase(1);
    
    EXPECT_EQ(arr.Size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, PopBack) {
    Array<int> arr;
    arr.PushBack(1);
    arr.PushBack(2);
    
    arr.PopBack();
    
    EXPECT_EQ(arr.Size(), 1);
    EXPECT_EQ(arr[0], 1);
}

TEST(ArrayTest, Clear) {
    Array<int> arr;
    arr.PushBack(1);
    arr.PushBack(2);
    
    arr.Clear();
    
    EXPECT_EQ(arr.Size(), 0);
    EXPECT_TRUE(arr.Empty());
}

TEST(PolymorphicTest, FigurePointers) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.PushBack(std::make_shared<Square<double>>(Point<double>{0, 0}, 2.0));
    figures.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, 3.0, 4.0));
    figures.PushBack(std::make_shared<Trapezoid<double>>());
    
    EXPECT_EQ(figures.Size(), 3);
    
    for (size_t i = 0; i < figures.Size(); ++i) {
        EXPECT_GT(figures[i]->Area(), 0.0);
    }
    
    double total = 0.0;
    for (size_t i = 0; i < figures.Size(); ++i) {
        total += figures[i]->Area();
    }
    EXPECT_GT(total, 0.0);
}

TEST(PolymorphicTest, CastToDouble) {
    Square<double> s(Point<double>{0, 0}, 3.0);
    double area = static_cast<double>(s);
    EXPECT_DOUBLE_EQ(area, 9.0);
    
    Rectangle<double> r(Point<double>{0, 0}, 4.0, 2.0);
    area = static_cast<double>(r);
    EXPECT_DOUBLE_EQ(area, 8.0);
}

TEST(PolymorphicTest, EqualityOperator) {
    Square<double> s1(Point<double>{0, 0}, 2.0);
    Square<double> s2(Point<double>{0, 0}, 2.0);
    Square<double> s3(Point<double>{1, 1}, 2.0);
    
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
}

TEST(LabRequirementsTest, SmartPointersInFigure) {
    Square<double> s(Point<double>{0, 0}, 2.0);
    
    EXPECT_NO_THROW({
        for (size_t i = 0; i < s.VerticesCount(); ++i) {
            auto& point = s.Vertex(i);
            EXPECT_NO_THROW(point.x);
            EXPECT_NO_THROW(point.y);
        }
    });
}

TEST(LabRequirementsTest, ArrayWithFigurePointers) {
    Array<Figure<double>*> rawArray;
    
    rawArray.PushBack(new Square<double>(Point<double>{0, 0}, 2.0));
    rawArray.PushBack(new Rectangle<double>(Point<double>{0, 0}, 3.0, 4.0));
    
    EXPECT_EQ(rawArray.Size(), 2);
    EXPECT_DOUBLE_EQ(rawArray[0]->Area(), 4.0);
    EXPECT_DOUBLE_EQ(rawArray[1]->Area(), 12.0);
    
    for (size_t i = 0; i < rawArray.Size(); ++i) {
        delete rawArray[i];
    }
}

TEST(LabRequirementsTest, ArrayWithSquares) {
    Array<Square<double>> squares;
    
    squares.PushBack(Square<double>(Point<double>{0, 0}, 2.0));
    squares.PushBack(Square<double>(Point<double>{5, 5}, 3.0));
    
    EXPECT_EQ(squares.Size(), 2);
    EXPECT_DOUBLE_EQ(squares[0].Area(), 4.0);
    EXPECT_DOUBLE_EQ(squares[1].Area(), 9.0);
    
    Array<Square<double>> copied = squares;
    EXPECT_EQ(copied.Size(), 2);
    
    Array<Square<double>> moved = std::move(squares);
    EXPECT_EQ(moved.Size(), 2);
    EXPECT_EQ(squares.Size(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}