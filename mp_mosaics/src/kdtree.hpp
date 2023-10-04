/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
#include <stdexcept>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    if (curDim >= Dim) {
        throw std::runtime_error("curDim is out of bounds");
    }
    // V2
    if (first[curDim] == second[curDim]) {
        return first < second;
    }
    return first[curDim] < second[curDim];
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    // V1
    // Calc distance between potential/ currentBest and target
    // Need dimension data. actually its just 3 since 3D
    // For loop to do ^2 calc and sum for each. ignore sqrt and use * instead of pow
    double currSum = 0;
    double potSum = 0;
    for (int i = 0; i < Dim; ++i) {
        currSum += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
        potSum += (potential[i] - target[i]) * (potential[i] - target[i]);
    }
    // Return compare
    return potSum < currSum;
}

// Helper function for constructor
// Accepts points vector that changes as it goes down
// start and end indexes to know where to look 
// and the current dimension to consider
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildHelper(typename vector<Point<Dim>>::iterator start, 
                                                           typename vector<Point<Dim>>::iterator end, 
                                                           int curDim) {
    cout << "FUNCTION: buildHelper executing" << endl;
    // cout << "start: " << start << " end: " << end << endl;
    // Base case, nothing left to consider/ nullptr case
    if (start >= end) {
        return nullptr;
    }
    // lambda function for select compare input, needs curDim
    auto cmp = [curDim](const Point<Dim>& a, const Point<Dim>& b) {
        return smallerDimVal(a, b, curDim);
    };
    // median we are looking for per spec
    auto median = start + ((end - start - 1) / 2);
    select(start, end, median, cmp);

    // New node with median pt
    KDTreeNode* node = new KDTreeNode(*median);

    // Recurse for left and right subtree
    curDim = (curDim + 1) % Dim;
    node->left = buildHelper(start, median, curDim);
    node->right = buildHelper(median + 1, end, curDim);

    // Return node for connecting to parent nodes 
    return node;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    cout << "FUNCTION: KDTree executing" << endl;
    // V1
    // if (newPoints.empty()) {
    //     root = nullptr;
    //     size = 0;
    //     return;
    // }
    size = newPoints.size();
    // copy of newPoints
    vector<Point<Dim>> points = newPoints;
    // curDim starts at 0
    root = buildHelper(points.begin(), points.end(), 0);
}

// helper function for deep copy constructor and assignment
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copyHelper(KDTreeNode* other) {
    if (other == nullptr) {
        return nullptr;
    }

    KDTreeNode* newNode = new KDTreeNode(other->point);
    newNode->left = copyHelper(other->left);
    newNode->right = copyHelper(other->right);

    return newNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
    size = other.size;
    root = copyHelper(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
    // Check if its the same
    if (this == &rhs) { return *this; }
    // delete current tree
    destroy(root);
    size = rhs.size;
    root = copyHelper(rhs.root);
    return *this;
}

// helper to destroy tree
template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* node) {
    if (node == nullptr) { return; }
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  destroy(root);
  size = 0;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

// Note: cmp compare function true if arg1 is less than arg2
// wank ass sorting algo helper function
// Assumes end is one past
template <typename RandIter, typename Comparator>
RandIter partitionHelper(RandIter start, RandIter end, RandIter pivot, Comparator cmp)
{
    cout << "FUNCTION: partitionHelper executing" << endl;
    // cout << "start: " << *start << " end: " << *(--end) << endl;
    // use start as pivot
    std::swap(*start, *pivot);
    RandIter i = start + 1;
    RandIter j = end - 1;

    // run until i overtakes j
    while (i <= j) {
        // move i right till ovetake or find ele greater than pivot
        // cout << "i: " << *i << " j: " << *j << " pivot: " <<*pivot << endl;
        while (i <= j && cmp(*i, *pivot)) {
            ++i;
            //cout << "i: " << *i << endl;
        }
        // same shit, till j is less than pivot
        while (i <= j && cmp(*pivot, *j)) {
            //cout << " j != start: " << (j != start) << endl;
            --j;
            //cout << " j: " << *j << endl;
            //cout << "Address j: " << &(*j) << " Address start: " << &(*start) << endl;
            //if (j == start) { break; }
        }
        // swap values and increment
        if (i < j) {
            std::swap(*i,*j);
        }
    }
    // Throw pivot to 'centre' which is at j
    std::swap(*pivot, *j);
    // return iterator j for use ltr
    return j;
}

// Seems like it works but imma mark this WIP
template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    cout << "FUNCTION: select executing" << endl;
    // Implement quick select/ quick sort algo
    // Check for single ele list, invalid start and if start is after end
    // cout << "start: " << *start << " end - 1: " << *(end - 1) << endl;;
    if (start >= end) { return; }

    // partitioning
    RandIter pivot = partitionHelper(start, end, start, cmp);

    // Case 1: K correct pos, return
    // Case 2: K wrong pos, on left of pivot, select that range
    // case 3: K wrong pos, right of pivot, select that range
    if (k == pivot) {
        return;
    } else if (k < pivot) {
        return select(start, pivot, k, cmp);
    } else {
        return select(pivot + 1, end, k, cmp);
    }
}

