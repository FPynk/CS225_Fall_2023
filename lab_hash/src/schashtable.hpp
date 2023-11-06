/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */
#include <iostream>
#include "schashtable.h"
 
template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    // Ensure we have the correct 'size' variable that represents the current size of the table.
    size_t idx = hashes::hash(key, size);  // Use the current size of the hash table.

    // Create a pair and insert it into the table at the hashed index.
    std::pair<K, V> p(key, value);
    table[idx].push_front(p);

    // Increment the count of elements in the table.
    this->elems++;
    // do we need to resize
    if (shouldResize()) {
        resizeTable();
    }
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key) {
            table[idx].erase(it);
            elems--;
            return;
        }
    }
    
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    if (size == 0) {  // Directly using 'size' is fine here too
        throw std::out_of_range("Hash table is empty");
    }
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }
    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    // calculate new size using findPrime
    size_t newSize = findPrime(size * 2);
    std::cout << "size: " << size << " newSize: " << newSize << std::endl;

    // create new table of new size
    std::list<std::pair<K, V>> *newTable = new std::list<std::pair<K, V>>[newSize];

    // Rehash elements
    typename std::list<std::pair<K, V>>::iterator it;
    for (size_t i = 0; i < size; i++) {
        for (it = table[i].begin(); it != table[i].end(); it++) {
            size_t newIdx = hashes::hash(it->first, newSize);
            newTable[newIdx].push_front(std::move(*it));
        }
    }

    // Swapping 
    std::list<std::pair<K, V>> *oldTable = table;
    table = newTable;
    size = newSize;

    // Cleanup
    delete[] oldTable;

    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
}
