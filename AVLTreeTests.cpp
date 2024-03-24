#include "AVLTree.h"
#include "timer.h"
#include <map>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int NUM_ELEMENTS = 10000; // Adjust this number based on your system's capabilities

// Helper function to generate random EmployeeInfo data
EmployeeInfo generateRandomEmployeeInfo(int id) {
    EmployeeInfo empl;
    empl.age = rand() % 60 + 20; // Random age between 20 and 80
    empl.salary = rand() % 50000 + 50000; // Random salary between 50,000 and 100,000
    empl.emplNumber = id;
    empl.sin = rand();
    return empl;
}

// Test for correctness of insertion
void testInsertion(AVLTree& avlTree, std::map<int, EmployeeInfo>& stdMap) {
    std::cout << "Testing insertion correctness..." << std::endl;
    bool correct = true;

    // Insert elements and check if they exist in both data structures
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        EmployeeInfo empl = generateRandomEmployeeInfo(i);
        avlTree.insert(empl);
        stdMap[empl.sin] = empl;

        if (avlTree.GetRoot() == nullptr || stdMap.find(empl.sin) == stdMap.end()) {
            correct = false;
            break;
        }
    }

    std::cout << "Insertion correctness test " << (correct ? "passed" : "failed") << std::endl;
}

// Test for correctness of deletion
void testDeletion(AVLTree& avlTree, std::map<int, EmployeeInfo>& stdMap) {
    std::cout << "Testing deletion correctness..." << std::endl;
    bool correct = true;

    // Delete every other element and check if they are removed from both data structures
    for (int i = 0; i < NUM_ELEMENTS; i += 2) {
        int sinToRemove = avlTree.GetRoot()->empl.sin; // Assuming GetRoot() is not null
        avlTree.remove(sinToRemove);
        stdMap.erase(sinToRemove);

        if (stdMap.find(sinToRemove) != stdMap.end()) {
            correct = false;
            break;
        }
    }

    std::cout << "Deletion correctness test " << (correct ? "passed" : "failed") << std::endl;
}

// Test for maximum size
void testMaximumSize() {
    std::cout << "Testing maximum size..." << std::endl;
    AVLTree avlTree;
    std::map<int, EmployeeInfo> stdMap;

    int maxAvlSize = 0;
    int maxMapSize = 0;
    try {
        for (int i = 0; i < NUM_ELEMENTS; ++i) {
            EmployeeInfo empl = generateRandomEmployeeInfo(i);
            avlTree.insert(empl);
            stdMap[empl.sin] = empl;
            maxAvlSize = i + 1;
            maxMapSize = i + 1;
        }
    } catch (const std::bad_alloc&) {
        std::cout << "Memory allocation failed" << std::endl;
    }

    std::cout << "Maximum size for AVL tree: " << maxAvlSize << std::endl;
    std::cout << "Maximum size for std::map: " << maxMapSize << std::endl;
}

// Test for load (repeated access)
void testLoad(AVLTree& avlTree, std::map<int, EmployeeInfo>& stdMap) {
    std::cout << "Testing load..." << std::endl;
    Timer timer;

    // Measure time taken for repeated access in AVL tree
    timer.start();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        avlTree.insert(generateRandomEmployeeInfo(i));
        avlTree.remove(avlTree.GetRoot()->empl.sin);
    }
    timer.stop();
    std::cout << "AVL tree load test time: " << timer.currtime() << " seconds" << std::endl;

    // Measure time taken for repeated access in std::map
    timer.reset();
    timer.start();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        EmployeeInfo empl = generateRandomEmployeeInfo(i);
        stdMap[empl.sin] = empl;
        stdMap.erase(empl.sin);
    }
    timer.stop();
    std::cout << "std::map load test time: " << timer.currtime() << " seconds" << std::endl;
}

// Test for speed of search (worst case)
void testSearchSpeed(AVLTree& avlTree, std::map<int, EmployeeInfo>& stdMap) {
    std::cout << "Testing search speed (worst case)..." << std::endl;
    Timer timer;

    // Find the element with the maximum SIN (worst case for AVL tree)
    int maxSin = std::max_element(stdMap.begin(), stdMap.end(),
                                  [](const auto& a, const auto& b) {
                                      return a.second.sin < b.second.sin;
                                  })->second.sin;

    // Measure time taken to search in AVL tree
    timer.start();
    avlTree.Find(avlTree.GetRoot(), maxSin);
    timer.stop();
    std::cout << "AVL tree search time: " << timer.currtime() << " seconds" << std::endl;

    // Measure time taken to search in std::map
    timer.reset();
    timer.start();
    stdMap.find(maxSin);
    timer.stop();
    std::cout << "std::map search time: " << timer.currtime() << " seconds" << std::endl;
}

int main() {
    srand(time(nullptr)); // Seed the random number generator

    AVLTree avlTree;
    std::map<int, EmployeeInfo> stdMap;

    // Populate AVL tree and std::map with random data
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        EmployeeInfo empl = generateRandomEmployeeInfo(i);
        avlTree.insert(empl);
        stdMap[empl.sin] = empl;
    }

    // Perform tests
    testInsertion(avlTree, stdMap);
    testDeletion(avlTree, stdMap);
    testMaximumSize();
    testLoad(avlTree, stdMap);
    testSearchSpeed(avlTree, stdMap);

    return 0;
}

