#include "dsets.h"
#include <iostream>

void DisjointSets::addelements(int num) {
    // resize to add num elements and set to -1
    set_collection_.resize(set_collection_.size() + num, -1);
}

// helper function for find: functions almost the same except it updates a path vector
// path will be used later to update all elements to point towards root
int DisjointSets::findHelper(int elem, std::vector<int> &path) {
    // std::cout << "FindHelper: " << elem << std::endl;
    // recursion logic to find root elem
    if (set_collection_[elem] < 0) {
        return elem;
    } else {
        // add elem to path
        path.push_back(elem);
        return findHelper(set_collection_[elem], path);
    }
}

int DisjointSets::find(int elem) {
    //std::cout << "Find: " << elem << std::endl;
    // if root is found first
    if (set_collection_[elem] < 0) {
        return elem;
    } else {
        // path vector to keep track of path
        std::vector<int> path;
        path.push_back(elem);
        // call helper to recurse for us
        int result = findHelper(set_collection_[elem], path);
        // setting all elements in path to point to root
        for (int idx : path) {
            set_collection_[idx] = result;
        }
        // return result
        return result;
    }
}

void DisjointSets::setunion(int a, int b) {
    // TODO
    // find root of a and b
    int a_root = find(a);
    int b_root = find(b);
    // std::cout << a << " root: " << a_root << std::endl;
    // std::cout << b << " root: " << b_root << std::endl;
    // if they are the same
    if (a_root == b_root) {
        return;
    }

    // get size of a and b
    //std::cout << "set_collection_[a_root]: " << set_collection_[a_root] << std::endl;
    signed int a_size = set_collection_[a_root];
    signed int b_size = set_collection_[b_root];
    //std::cout << a << " size: " << a_size << std::endl;
    //std::cout << b << " size: " << b_size << std::endl;
    // compare and connect smaller to larger
    // since they are negative, more negative is larger
    // 3 cases: a larger, b larger and equal (b -> a)
    if (a_size < b_size) {
        // point b to a
        set_collection_[b_root] = a_root;
        // update size
        set_collection_[a_root] += b_size;
    } else if (b_size < a_size) {
        // point a to b
        set_collection_[a_root] = b_root;
        // update size
        set_collection_[b_root] += a_size;
    } else {
        // redundant code but im lazy
        // point b to a
        set_collection_[b_root] = a_root;
        // update size
        set_collection_[a_root] += b_size;
    }
}

int DisjointSets::size(int elem) {
    return -1 * set_collection_[find(elem)];
}

void DisjointSets::printSet() {
    std::cout << "Set Collection: ";
    for (int elem : set_collection_) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}