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

    std::cout << "List<int> contents: ";
    for (auto it = test_int.begin(); it != test_int.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    test_char.insertFront('c');
    test_char.insertFront('b');
    test_char.insertFront('a');
    test_char.insertBack('d');
    test_char.insertBack('e');
    test_char.insertBack('f');

    std::cout << "List<char> contents: ";
    for (auto it = test_char.begin(); it != test_char.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Success!" << std::endl;
    return 0;
}
