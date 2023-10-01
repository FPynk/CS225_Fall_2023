/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node* output = find(root, key);
    if (output == NULL) {
        throw std::runtime_error("Key not found");
    }
    return output->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (!subtree) {
        static Node* nullNode = NULL;
        return nullNode;
    }

    if (subtree->key == key) {
        return subtree;
    } else if (subtree->key > key) {
        return find(subtree->left, key);
    } else {
        return find(subtree->right, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    if (find(key, value) == NULL) {
        insert(root, key, value);
    }
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
        return;
    }
    if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else {
        insert(subtree->right, key, value);
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    std::swap(first->value, second->value);
    std::swap(first->key, second->key);
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    // if (find(key)) {
    //     return;
    // }
    try {
        V idk = find(key);
        remove(root, key);
    } catch (const std::runtime_error& e) {
        return;
    }
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    if (subtree == NULL) {
        return;
    }
    if (subtree->key == key) {                                      // Node found
        if (subtree->left != NULL && subtree->right != NULL) {      // 2 Children
            // find IOP, right most node in left subtree
            Node* iop = subtree->left;
            while (iop->right != NULL) {
                iop = iop->right;
            }
            swap(iop, subtree);
            remove(iop, key);
        } else {                                                    // 1 Child
            Node* tmp = subtree;
            if (subtree->left != NULL) {                            // left child
                subtree = subtree->left;
            } else {                                                // right child
                subtree = subtree->right;
            }
            delete tmp;
        }
    } else if (subtree->key > key) {
        remove(subtree->left, key);
    } else {
        remove(subtree->right, key);
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> output;
    for (unsigned int i = 0; i < inList.size(); ++i) {
        output.insert(inList[i].first, inList[i].second);
    }
    return output;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::sort(inList.begin(), inList.end());
    std::vector<int> output;
    int h = listBuild(inList).height();
    output.resize(h + 1, 0);
    output[h]++;
    while (std::next_permutation(inList.begin(), inList.end())) {
        if (h >= static_cast<int>(output.size())) {
            output.resize(h + 1, 0);
        }
        output[listBuild(inList).height()]++;
    }
    return output;
}