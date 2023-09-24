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
TEST_CASE("ListIterator::IterateFromEnd", "") {
    List<int> myList;
    myList.insertBack(1);
    myList.insertBack(2);
    myList.insertBack(3);
    myList.insertBack(4);
    myList.insertBack(5);

    auto iter = myList.end();

    // Assuming that your end() returns an iterator pointing to one past the last element
    // and that your -- operator handles this correctly to point to the last element
    --iter;
    REQUIRE(*iter == 5);
    --iter;
    REQUIRE(*iter == 4);
    --iter;
    REQUIRE(*iter == 3);
    --iter;
    REQUIRE(*iter == 2);
    --iter;
    REQUIRE(*iter == 1);
}