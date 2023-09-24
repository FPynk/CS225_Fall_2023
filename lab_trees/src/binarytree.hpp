/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    return mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) {
    // base case
    if (!subRoot) {
        return;
    }
    // swapping
    std::swap(subRoot->right, subRoot->left);
    // recursion
    mirror(subRoot->right);
    mirror(subRoot->left);
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    // keep track of who we need to visit
    std::stack<Node*> stack;
    // traversal node
    Node* curr = root;
    // changed to literal min val available
    T lastVisited = std::numeric_limits<T>::min();

    while (!stack.empty() || curr != NULL) {
        // not null, go left
        if (curr != NULL) {
            stack.push(curr);
            curr = curr->left;
        // is null, at leaf, backtrack, use stack to go back and go right
        } else {
            curr = stack.top();
            stack.pop();
            // if firstNode that we are backtracking, its leftmost, start lastVisited
            if (curr->elem < lastVisited) {
                std::cout << "Failing at node: " << curr->elem << " lastVisited: " << lastVisited << std::endl;
                return false;
            }
            // update val
            lastVisited = curr->elem;
            curr = curr->right;
        }
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    // use of numeric limits for recursive function
    return isOrderedRecursiveHelper(root, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursiveHelper(Node* root, T min, T max) const {
    // base case leaf
    if (root == NULL) {
        return true;
    }
    // comparing against right and against left
    if (root->elem < min || root->elem > max) {
        return false;
    }
    // recursive step
    return isOrderedRecursiveHelper(root->left, min, root->elem) && isOrderedRecursiveHelper(root->right, root->elem, max);
}

