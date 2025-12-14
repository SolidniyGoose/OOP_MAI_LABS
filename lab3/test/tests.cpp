#include <gtest/gtest.h>
#include "Point.hpp"
#include "Figure.hpp"
#include "Trapezoid.hpp"
#include "Rhomb.hpp"
#include "Pentagon.hpp"
#include "FigureArray.hpp"

TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(3.5, 2.1);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 2.1);
}

TEST(PointTest, EqualityOperator) {
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(3.0, 4.0);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, InequalityOperator) {
    Point p1(1.0, 2.0);
    Point p2(3.0, 4.0);
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 != p1);
}

TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid t;
    EXPECT_EQ(t.VerticesCount(), 4);
    EXPECT_GT(t.Area(), 0.0);
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid t(Point(0,0), Point(4,0), Point(3,2), Point(1,2));
    Point center = t.Center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RhombTest, DefaultConstructor) {
    Rhomb r;
    EXPECT_EQ(r.VerticesCount(), 4);
    EXPECT_GT(r.Area(), 0.0);
}

TEST(RhombTest, AreaCalculation) {
    Rhomb r(Point(0,0), Point(2,3), Point(4,0), Point(2,-3));
    EXPECT_DOUBLE_EQ(r.Area(), 12.0);
}

TEST(PentagonTest, DefaultConstructor) {
    Pentagon p;
    EXPECT_EQ(p.VerticesCount(), 5);
    EXPECT_GT(p.Area(), 0.0);
}

TEST(FigureArrayTest, DefaultConstructor) {
    FigureArray arr;
    EXPECT_EQ(arr.Size(), 0);
    EXPECT_TRUE(arr.IsEmpty());
}

TEST(FigureArrayTest, PushBackAndSize) {
    FigureArray arr;
    arr.PushBack(new Trapezoid());
    arr.PushBack(new Rhomb());
    EXPECT_EQ(arr.Size(), 2);
    EXPECT_FALSE(arr.IsEmpty());
}

TEST(FigureArrayTest, EraseElement) {
    FigureArray arr;
    arr.PushBack(new Trapezoid());
    arr.PushBack(new Rhomb());
    arr.PushBack(new Pentagon());
    
    arr.Erase(1);
    EXPECT_EQ(arr.Size(), 2);
    
    EXPECT_NE(dynamic_cast<Trapezoid*>(arr[0]), nullptr);
    EXPECT_NE(dynamic_cast<Pentagon*>(arr[1]), nullptr);
}

TEST(FigureArrayTest, CopyConstructor) {
    FigureArray arr1;
    arr1.PushBack(new Trapezoid());
    arr1.PushBack(new Rhomb());
    
    FigureArray arr2(arr1);
    EXPECT_EQ(arr1.Size(), arr2.Size());
    
    EXPECT_NE(arr1[0], arr2[0]);
    EXPECT_NE(arr1[1], arr2[1]);
}

TEST(FigureArrayTest, MoveConstructor) {
    FigureArray arr1;
    arr1.PushBack(new Trapezoid());
    
    FigureArray arr2(std::move(arr1));
    EXPECT_EQ(arr1.Size(), 0);
    EXPECT_EQ(arr2.Size(), 1);
    EXPECT_TRUE(arr1.IsEmpty());
}

TEST(FigureArrayTest, AssignmentOperator) {
    FigureArray arr1;
    arr1.PushBack(new Trapezoid());
    
    FigureArray arr2;
    arr2 = arr1;
    
    EXPECT_EQ(arr1.Size(), arr2.Size());
    EXPECT_NE(arr1[0], arr2[0]);
}

TEST(FigureArrayTest, ClearMethod) {
    FigureArray arr;
    arr.PushBack(new Trapezoid());
    arr.PushBack(new Rhomb());
    
    arr.Clear();
    EXPECT_EQ(arr.Size(), 0);
    EXPECT_TRUE(arr.IsEmpty());
}

TEST(FigureArrayTest, FrontAndBack) {
    FigureArray arr;
    Trapezoid* t = new Trapezoid();
    Rhomb* r = new Rhomb();
    
    arr.PushBack(t);
    arr.PushBack(r);
    
    EXPECT_EQ(arr.Front(), t);
    EXPECT_EQ(arr.Back(), r);
}

TEST(FigureArrayTest, OutOfRangeAccess) {
    FigureArray arr;
    EXPECT_THROW(arr.at(0), std::out_of_range);
    
    arr.PushBack(new Trapezoid());
    EXPECT_NO_THROW(arr.at(0));
    EXPECT_THROW(arr.at(1), std::out_of_range);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
