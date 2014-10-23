/**
 * @file Main.cpp
 * @author Zhang Hai
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "BinaryHeap.h"
#include "VectorCBTree.h"
#include "Sort.h"

template<typename T>
void printVector(std::vector<T> &vector) {
    bool first = true;
    for (int &element : vector) {
        if (first) {
            first = false;
        } else {
            std::cout << " ";
        }
        std::cout << element;
    }
    std::cout << std::endl;
}

void run() {

    std::vector<int> data = {10, 12, 1, 14, 6, 5, 8, 15, 3, 9, 7, 4,
            11, 13, 2};

    BinaryHeap<int> heap1;
    for (int &element : data) {
        heap1.insert(element);
    }
    heap1.print();
    for (int i = 0; i < 3; ++i) {
        heap1.removeMin();
    }
    heap1.print();

    std::cout << std::endl;

    // Workaround "Most Vexing Parse".
    BinaryHeap<int> heap2((VectorCBTree<int>(data)));
    heap2.print();
    for (int i = 0; i < 3; ++i) {
        heap2.removeMin();
    }
    heap2.print();

    std::cout << std::endl;

    printVector(data);
    quickSort(data.begin(), data.end());
    printVector(data);
}

int main() {
    run();
    return EXIT_SUCCESS;
}
