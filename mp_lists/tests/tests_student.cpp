#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {
    // lol
    bool student_wrote_test_case = true;

    REQUIRE( student_wrote_test_case );
}

TEST_CASE("ListIterator::operator-- from beginning", "") {
    List<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    auto iter = list.begin();
    --iter;  // Should not crash, but behavior is undefined. Usually, it should stay at the beginning.
    REQUIRE( *iter == 1 );
}

TEST_CASE("ListIterator::operator-- general case", "") {
    List<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    auto iter = list.begin();
    ++iter;
    ++iter;
    --iter;

    REQUIRE( *iter == 2 );
}

TEST_CASE("ListIterator::operator--(int) from beginning", "") {
    List<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    auto iter = list.begin();
    iter--;  // Should not crash, but behavior is undefined. Usually, it should stay at the beginning.

    REQUIRE( *iter == 1 );
}

TEST_CASE("ListIterator::operator--(int) general case", "") {
    List<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    auto iter = list.begin();
    ++iter;
    ++iter;
    iter--;

    REQUIRE( *iter == 2 );
}