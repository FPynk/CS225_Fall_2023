#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>

#include "cs225/point.h"

#include "kdtree.h"

#include "tests_part1.h"
// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

// TEST_CASE("My Test Case", "[student]") {
//     bool student_wrote_test_case = false;

//     REQUIRE( student_wrote_test_case );
// }

template<typename T>
void printArray(const std::vector<T>& arr, const std::string& label) {
    std::cout << label << "[ ";
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << "]" << std::endl;
}

TEST_CASE("select on already sorted array", "[student]") {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto cmp = [](int lhs, int rhs) { return lhs <= rhs; };
    printArray(numbers, "Before select: ");
    cout << "k: " << *(std::begin(numbers) + 4) << endl;
    select(std::begin(numbers), std::end(numbers), std::begin(numbers) + 4, cmp);
    printArray(numbers, "After select: ");
    REQUIRE(!isSorted(numbers.begin(), numbers.end(), cmp));
    REQUIRE(numbers[4] == 5);
}

TEST_CASE("select simple 1", "[student]") {
    std::vector<int> numbers = {2, 6, 3, 4, 1, 9, 7, 9, 5};
    auto cmp = [](int lhs, int rhs) { return lhs <= rhs; };
    printArray(numbers, "Before select: ");
    select(std::begin(numbers), std::end(numbers), std::begin(numbers) + 4, cmp);
    printArray(numbers, "After select: ");
    REQUIRE(!isSorted(numbers.begin(), numbers.end(), cmp));
    REQUIRE(numbers[4] == 5);
}

TEST_CASE("select simple 2", "[student]") {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    auto cmp = [](int lhs, int rhs) { return lhs <= rhs; };
    printArray(numbers, "Before select: ");
    select(std::begin(numbers), std::end(numbers), std::begin(numbers) + 3, cmp);
    printArray(numbers, "After select: ");
    REQUIRE(!isSorted(numbers.begin(), numbers.end(), cmp));
    REQUIRE(numbers[3] == 3);
}

TEST_CASE("select simple 3", "[student]") {
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    auto cmp = [](int lhs, int rhs) { return lhs <= rhs; };
    printArray(numbers, "Before select: ");
    select(std::begin(numbers), std::end(numbers), std::begin(numbers) + 0, cmp);
    printArray(numbers, "After select: ");
    REQUIRE(!isSorted(numbers.begin(), numbers.end(), cmp));
    REQUIRE(numbers[0] == 10);
}

TEST_CASE("select simple 4", "[student]") {
    std::vector<int> numbers = {99, 88, 77, 66, 55};
    auto cmp = [](int lhs, int rhs) { return lhs <= rhs; };
    printArray(numbers, "Before select: ");
    select(std::begin(numbers), std::end(numbers), std::begin(numbers) + 2, cmp);
    printArray(numbers, "After select: ");
    REQUIRE(!isSorted(numbers.begin(), numbers.end(), cmp));
    REQUIRE(numbers[2] == 77);
}

TEST_CASE("select simple 5", "[student]") {
    std::vector<int> numbers = {1, 1, 1, 1, 1};
    auto cmp = [](int lhs, int rhs) { return lhs <= rhs; };
    printArray(numbers, "Before select: ");
    select(std::begin(numbers), std::end(numbers), std::begin(numbers) + 2, cmp);
    printArray(numbers, "After select: ");
    REQUIRE(!isSorted(numbers.begin(), numbers.end(), cmp));
    REQUIRE(numbers[2] == 1);
}