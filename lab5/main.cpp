#include <iostream>

#include "Queue.hpp"
#include "DynamicMemory.hpp"

struct ExampleData {
    int id;
    double value;
};

int main() {
    std::cout << "=== Queue ===\n";

    DynamicListMemory memory;

    std::cout << "\nQueue<int>:\n";
    Queue<int> intQueue(&memory);

    intQueue.push(10);
    intQueue.push(20);
    intQueue.push(30);

    std::cout << "Contents: ";
    for (int x : intQueue) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "Front: " << intQueue.front() << "\n";
    intQueue.pop();
    std::cout << "Front after: " << intQueue.front() << "\n";

    std::cout << "\nQueue<ExampleData>:\n";
    Queue<ExampleData> structQueue(&memory);

    structQueue.push({1, 1.5});
    structQueue.push({2, 2.5});
    structQueue.push({3, 3.5});

    std::cout << "Contents:\n";
    for (const auto& elem : structQueue) {
        std::cout << "id = " << elem.id << ", value = " << elem.value << "\n";
    }

    std::cout << "\nRemoving elem:\n";
    while (!structQueue.empty()) {
        auto& front = structQueue.front();
        std::cout << "Pop: id = " << front.id
                  << ", value = " << front.value << "\n";
        structQueue.pop();
    }

    std::cout << "\nQueue is empty: "
              << std::boolalpha << structQueue.empty() << "\n";

    return 0;
}
