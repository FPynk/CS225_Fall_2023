/**
 * @file testdsets.cpp
 * Performs basic tests of DisjointSets.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"

using std::cout;
using std::endl;

int main()
{
    DisjointSets s;

    s.addelements(50);
    s.setunion(2, 3);
    s.printSet();
    s.setunion(3, 5);
    s.printSet();
    s.setunion(5, 7);
    s.printSet();
    s.setunion(7, 2);
    s.printSet();
    s.setunion(4, 6);
    s.printSet();

    cout << s.find(7) << endl;
    cout << s.find(5) << endl;
    cout << s.find(6) << endl;

    s.addelements(1);

    cout << s.find(50) << endl;

    s.setunion(50, 3);

    cout << s.find(50) << endl;
    cout << "Disjoint Sets test complete" << endl;

    return 0;
}
