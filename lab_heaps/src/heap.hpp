
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // return the index you are choosing to be your root.: 1 indexed
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // return the index of the left child.
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // return the index of the right child.
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // return the index of the parent.
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // return whether the given node has a child
    // Check elems can fit child, WIP may have to check if child is valid/ exists
    return _elems.size() > (currentIdx * 2);
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    //std::cout << "currentIdx for MPC: " << currentIdx << std::endl;
    int lc_idx = leftChild(currentIdx);
    // int rc_idx = rightChild(currentIdx);
    T leftChild = _elems[lc_idx];
    if (lc_idx >= static_cast<int>(_elems.size())) {
        std::cout << "This is a leaf" << std::endl;
        return currentIdx;
    }
    int rc_idx = rightChild(currentIdx);
    // std::cout << "lc & rc idx for MPC: " << lc_idx << " | " << rc_idx << std::endl;
    // std::cout << "rc idx sub attempt, elems size: " << _elems.size() << std::endl;
    if (rc_idx >= static_cast<int>(_elems.size()) || higherPriority(leftChild, _elems[rc_idx])) {
        return lc_idx;
    }
    return rc_idx;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    //std::cout << "currentIdx for HD: " << currentIdx << std::endl;
    // check if its a leaf
    if (currentIdx == _elems.size() - 1 || _elems.size() == 1
        || leftChild(currentIdx) >= _elems.size()) {
        return;
    }
    size_t minChildIdx = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[minChildIdx], _elems[currentIdx])) {
        std::swap(_elems[minChildIdx], _elems[currentIdx]);
        heapifyDown(minChildIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    //std::cout << "currentIdx for HU: " << currentIdx << std::endl;
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems = elems;
    _elems.insert(_elems.begin(), T());
    for (int i = (_elems.size() / 2); i > 0; --i) {
        heapifyDown(i);    
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (empty()) {
        std::cout << "popping empty heap" << std::endl;
        return T();
    }
    T min = _elems[1];
    _elems[1] = _elems[_elems.size() - 1];
    _elems.pop_back();
    heapifyDown(1);
    return min;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    std::cout << "Pushing: " << elem << " size is now: " << _elems.size() << std::endl;
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    // added checks for root and leaf
    // if curr idx has higher priority than parent or child has higher priority, do correct heapify
    if (idx != root() && higherPriority(_elems[idx], _elems[parent(idx)])) {
        heapifyUp(idx);
    } else if (leftChild(idx) < _elems.size() && higherPriority(_elems[maxPriorityChild(idx)], _elems[idx])) {
        heapifyDown(idx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() == 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
