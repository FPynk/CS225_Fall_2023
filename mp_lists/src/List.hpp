/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
    ListNode* tmp = head_;
    while (head_ != nullptr) {
        tmp = head_->next;
        delete head_;
        head_ = tmp;
    }
    head_ = NULL;
    tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
    /// @todo Graded in mp_lists part 1
    ListNode * newNode = new ListNode(ndata);
    // Case 1: empty list
    if (head_ == NULL && tail_ == NULL) {
        head_ = newNode;
        tail_ = newNode;
    } else { // Case 2: 1 element list & Case 3: multi ele list
        newNode->next = head_;
        head_->prev = newNode;
        head_ = newNode;
    }
    length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
    // Case 1: empty list
    if (head_ == NULL && tail_ == NULL) {
        head_ = newNode;
        tail_ = newNode;
    } else { // Case 2: 1 element list & Case 3: multi ele list
        newNode->prev = tail_;
        tail_->next = newNode;
        tail_ = newNode;
    }
    length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL && curr->prev != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
    /// @todo Graded in part 1
    // case 1: empty or 1 element
    if (head_ == tail_) {
        return;
    }

    ListNode* cur = head_->next;
    while (cur != NULL && cur != tail_) {
        ListNode* move = cur;
        cur = cur->next->next;

        // linking 2 nodes
        move->prev->next = move->next;
        if (move->next != NULL) {
            move->next->prev = move->prev;
        }

        // relinking moving node
        move->prev = tail_;
        tail_->next = move;
        move->next = NULL;
        tail_ = move;
    }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
    //// @todo Graded in mp_lists part 2
    std::cout << "calling reverse helper" << std::endl;
    // Edge case, if 0 element or 1 element list, or invalid inputs
    if (startPoint == NULL || endPoint == NULL) { 
        std::cout << "NULL value detected" << std::endl;
        return; 
    }
    if (startPoint == endPoint) {
        std::cout << "1 element list" << std::endl;
        return; 
    }

    // Maintain pointer to surround nodes
    ListNode* beforeStart = startPoint->prev;
    ListNode* afterEnd = endPoint->next;
    // std::cout << "beforeStart " << beforeStart << std::endl;
    // std::cout << "afterEnd " << afterEnd << std::endl;
    // std::cout << "startPoint " << startPoint << std::endl;
    // std::cout << "endPoint " << endPoint << std::endl;
    // if (beforeStart != nullptr) {
    //         std::cout << "beforeStart: " << beforeStart->data << std::endl;
    //     } else {
    //         std::cout << "beforeStart: is nullptr" << std::endl;
    // }
    // if (afterEnd != nullptr) {
    //         std::cout << "afterEnd: " << afterEnd->data << std::endl;
    //     } else {
    //         std::cout << "afterEnd: is nullptr" << std::endl;
    // }
    // if (startPoint != nullptr) {
    //         std::cout << "startPoint: " << startPoint->data << std::endl;
    //     } else {
    //         std::cout << "startPoint: is nullptr" << std::endl;
    // }
    // if (endPoint != nullptr) {
    //         std::cout << "endPoint: " << endPoint->data << std::endl;
    //     } else {
    //         std::cout << "endPoint: is nullptr" << std::endl;
    // }
    // Track current node
    ListNode* curr = endPoint;
    // Track next node (in old direction)
    ListNode* next = NULL;
    ListNode* prev = NULL;

    // Stop when we reach startPoint
    while(curr != beforeStart && curr != NULL) {
        //std::cout << "Current node: " << curr->data << std::endl;
        next = curr->next;
        prev = curr->prev;
        curr->next = curr->prev;
        curr->prev = next;
        // if (curr->prev != nullptr) {
        //     std::cout << "curr->prev: " << curr->prev->data << std::endl;
        // } else {
        //     std::cout << "curr->prev: is nullptr" << std::endl;
        // }
        // if (curr->next != nullptr) {
        //     std::cout << "curr->next: " << curr->next->data << std::endl;
        // } else {
        //     std::cout << "curr->next: is nullptr " << std::endl;
        // }
        curr = prev;
    }

    if (beforeStart != NULL) {beforeStart->next = endPoint;}
    if (afterEnd != NULL) {afterEnd->prev = startPoint;}

    startPoint->next = afterEnd;
    endPoint->prev = beforeStart;
    ListNode* tmp = startPoint;
    startPoint = endPoint;
    endPoint = tmp;

    // if (beforeStart != nullptr) {
    //         std::cout << "beforeStart: " << beforeStart->data << std::endl;
    //     } else {
    //         std::cout << "beforeStart: is nullptr" << std::endl;
    // }
    // if (afterEnd != nullptr) {
    //         std::cout << "afterEnd: " << afterEnd->data << std::endl;
    //     } else {
    //         std::cout << "afterEnd: is nullptr" << std::endl;
    // }
    // if (startPoint != nullptr) {
    //         std::cout << "startPoint: " << startPoint->data << std::endl;
    //     } else {
    //         std::cout << "startPoint: is nullptr" << std::endl;
    // }
    // if (endPoint != nullptr) {
    //         std::cout << "endPoint: " << endPoint->data << std::endl;
    //     } else {
    //         std::cout << "endPoint: is nullptr" << std::endl;
    // }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
    /// @todo Graded in mp_lists part 2
    //std::cout << "calling reverseNth" << std::endl;
    if (n <= 0  || head_ == NULL) { return; }

    ListNode* startPoint = head_;
    ListNode* endPoint = head_;
    while (startPoint != NULL) {
        // Iterate until n or length_ reached
        for(int i = 1; i < n && endPoint->next != NULL; i++) {
            endPoint = endPoint->next;
        }
        //std::cout << "calling reverse on " << startPoint->data << " and " << endPoint->data << std::endl;
        if (startPoint == head_ && endPoint == tail_) {
            reverse(head_, tail_);
            startPoint = head_;
            endPoint = tail_;
        } else if (startPoint == head_) {
            reverse(head_, endPoint);
            startPoint = head_;
        } else if (endPoint == tail_) {
            reverse(startPoint, tail_);
            endPoint = tail_;
        } else {
            reverse(startPoint, endPoint);
        }
        startPoint = endPoint->next;
        endPoint = startPoint;
    }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
    /// @todo Graded in mp_lists part 2
    // check for NULL values
    if (first == NULL) { return second; }
    if (second == NULL) { return first; }

    // pointers for merged list
    ListNode* head = NULL;
    ListNode* tail = NULL;

    // set head of the merged list
    if (first->data < second->data) {
        head = tail = first;
        first = first->next;
    } else {
        head = tail = second;
        second = second->next;
    }

    while (first != NULL && second != NULL) {
        if (first->data < second->data) {
            tail->next = first;
            first->prev = tail;
            first = first->next;
        } else {
            tail->next = second;
            second->prev = tail;
            second = second->next;
        }
        tail = tail->next;
    }
    
    if (first != NULL) {
        tail->next = first;
        first->prev = tail;
    }
    if (second != NULL) {
        tail->next = second;
        second->prev = tail;
    }
    return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
    /// @todo Graded in mp_lists part 2
    // basecase
    if (chainLength <= 1) {return start;}

    // middle pt
    int mid = chainLength / 2;

    // pointers for iterating
    ListNode* midNode = start;
    ListNode* prev = nullptr;

  return NULL;
}
