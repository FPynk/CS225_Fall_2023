#include "List.h"
#include <iostream>

int main() {
    List<int> test_int;
    List<char> test_char;
    
    test_int.insertFront(3);
    test_int.insertFront(2);
    test_int.insertFront(1);
    test_int.insertBack(4);
    test_int.insertBack(5);
    test_int.insertBack(6);

    std::cout << "Success!" << std::endl;
    return 0;
}
