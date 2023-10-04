/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    // V1
    return first[curDim] <= second[curDim];
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
    for (int i = 0; i < 3; ++i) {
        currSum += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
        potSum += (potential[i] - target[i]) * (potential[i] - target[i]);
    }
    // Return compare
    return potSum < currSum;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
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
// Assuems end is inclusive, not one past
template <typename RandIter, typename Comparator>
RandIter partitionHelper(RandIter start, RandIter end, Comparator cmp)
{
    // use start as pivot
    RandIter pivot = start;
    RandIter i = start;
    RandIter j = end;

    // run until i overtakes j
    while (i <= j) {
        // move i right till ovetake or find ele greater than pivot
        while (i <= j && cmp(*i, *pivot)) {
            ++i;
        }
        // same shit, till j is less than pivot
        while (i <= j && cmp(*pivot, *j)) {
            --j;
        }
        // swap values and increment
        std::swap(*i,*j);
        ++i;
        --j;
    }
    // Throw pivot to 'centre' which is at j
    std::swap(*pivot, *j);
    // return iterator j for use ltr
    return j;
}


template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    // Implement quick select/ quick sort algo
    // Check for single ele list, invalid start and if start is after end
    if (start >= end) { return; }
    end = --end;
    cout << "made it past --end" << endl;
    // partitioning
    RandIter pivot = partitionHelper(start, end, cmp);

    // Case 1: K correct pos, return
    // Case 2: K wrong pos, on left of pivot, select that range
    // case 3: K wrong pos, right of pivot, select that range
    if (k == pivot) {
        return;
    } else if (k < pivot) {
        pivot = --pivot;
        return select(start, pivot, k, cmp);
    } else {
        return select(pivot, end, k, cmp);
    }
}

