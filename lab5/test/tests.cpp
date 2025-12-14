#include <gtest/gtest.h>

#include "Queue.hpp"
#include "DynamicMemory.hpp"

struct TestStruct {
    int a;
    double b;

    bool operator==(const TestStruct& other) const {
        return a == other.a && b == other.b;
    }
};

TEST(QueueIntTest, InitiallyEmpty) {
    DynamicListMemory mem;
    Queue<int> q(&mem);

    EXPECT_TRUE(q.empty());
}

TEST(QueueIntTest, PushAndFront) {
    DynamicListMemory mem;
    Queue<int> q(&mem);

    q.push(10);
    q.push(20);

    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.front(), 10);
}

TEST(QueueIntTest, PopWorksCorrectly) {
    DynamicListMemory mem;
    Queue<int> q(&mem);

    q.push(1);
    q.push(2);
    q.push(3);

    q.pop();
    EXPECT_EQ(q.front(), 2);

    q.pop();
    EXPECT_EQ(q.front(), 3);
}

TEST(QueueIntTest, PopFromEmptyThrows) {
    DynamicListMemory mem;
    Queue<int> q(&mem);

    EXPECT_THROW(q.pop(), std::runtime_error);
}

TEST(QueueIntTest, FrontFromEmptyThrows) {
    DynamicListMemory mem;
    Queue<int> q(&mem);

    EXPECT_THROW(q.front(), std::runtime_error);
}

TEST(QueueIteratorTest, IteratesInCorrectOrder) {
    DynamicListMemory mem;
    Queue<int> q(&mem);

    q.push(1);
    q.push(2);
    q.push(3);

    int expected = 1;
    for (int value : q) {
        EXPECT_EQ(value, expected++);
    }
}

TEST(QueueIteratorTest, EmptyQueueIteration) {
    DynamicListMemory mem;
    Queue<int> q(&mem);

    EXPECT_EQ(q.begin(), q.end());
}

TEST(QueueStructTest, WorksWithStructs) {
    DynamicListMemory mem;
    Queue<TestStruct> q(&mem);

    q.push({1, 1.1});
    q.push({2, 2.2});

    EXPECT_EQ(q.front(), (TestStruct{1, 1.1}));
    q.pop();
    EXPECT_EQ(q.front(), (TestStruct{2, 2.2}));
}

TEST(QueueStructTest, IteratorWithStructs) {
    DynamicListMemory mem;
    Queue<TestStruct> q(&mem);

    q.push({1, 1.1});
    q.push({2, 2.2});
    q.push({3, 3.3});

    TestStruct expected[] = {
        {1, 1.1},
        {2, 2.2},
        {3, 3.3}
    };

    int idx = 0;
    for (const auto& elem : q) {
        EXPECT_EQ(elem.a, expected[idx].a);
        EXPECT_DOUBLE_EQ(elem.b, expected[idx].b);
        ++idx;
    }
}

TEST(MemoryResourceTest, MultipleAllocations) {
    DynamicListMemory mem;
    Queue<int> q(&mem);

    for (int i = 0; i < 100; ++i) {
        q.push(i);
    }

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(q.front(), i);
        q.pop();
    }

    EXPECT_TRUE(q.empty());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
