/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */
    
    // Increment and resize if needed
    elems++;
    if (shouldResize()) {
        resizeTable();
    }
    // get idx of where to start
    size_t idx = hashes::hash(key, size);
    // Check if slot is filled or not
    if (table[idx] != nullptr) {
        for (unsigned int i = 0; i < size; i++) {
            // if key already exists, replace. If reach empty insert new ele
            unsigned int newIdx = (idx + i) % size;
            if (table[newIdx] != nullptr && table[newIdx]->first == key) {
                table[newIdx]->second = value;
                elems--;
                return;
            } else if (table[newIdx] == nullptr) {
                table[newIdx] = new std::pair<K, V>(key, value);
                should_probe[newIdx] = true;
                return;
            }
        }
    } else {
        // insert new element
        table[idx] = new std::pair<K, V>(key, value);
        should_probe[idx] = true;
    }

}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    // get idx starting point for key
    size_t idx = hashes::hash(key, size);

    // Check table for the key
    for (size_t i = 0; i < size; ++i) {
        size_t curIdx = (idx + i) % size;

        // If we hit a null, key is not in table
        if (table[curIdx] == nullptr) {
            return;
        }

        // Check if current slot contains key to remove
        if (table[curIdx] != nullptr && table[curIdx]->first == key) {
            // delete pair and set to nullptr
            delete table[curIdx];
            table[curIdx] = nullptr;

            // Decrement elems
            --elems;
            return;
        }
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    // compute initial index for given key
    size_t idx = hashes::hash(key, size);
    // prove table to find key
    for (size_t i =0; i < size; ++i) {
        size_t curIdx = (idx + i) % size;
        // if hit a nullptr, key not present
        if (!should_probe[curIdx]) {
            return -1;
        }
        // if not null and matching key
        if (table[curIdx] != nullptr && table[curIdx]->first == key) {
            return static_cast<int>(curIdx);
        }
    }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{
    /**
    * @todo Implement this function
    *
    * The size of the table should be the closest prime to size * 2.
    *
    * @hint Use findPrime()!
    */
    // calc new size
    size_t newSize = findPrime(2 * size);
    // allocate new aray of pointers
    std::pair<K, V>** newTable = new std::pair<K, V>*[newSize]();
    bool* newShouldProbe = new bool[newSize]();

    // rehash all preexisting elements
    for (size_t i =0; i < size; ++i) {
    //skip emtpy elements
        if (table[i] != nullptr) {
            // get new idx of current key
            size_t idx = hashes::hash(table[i]->first, newSize);
            // find free slot in new table to insert
            while (newTable[idx] != nullptr) {
                idx = (idx + 1) % newSize;
            }
            // place new element
            newTable[idx] = table[i];
            newShouldProbe[idx] = true;
        }
    }
    // delete old table
    delete[] table;
    delete[] should_probe;
    table = newTable;
    should_probe = newShouldProbe;
    size = newSize;
}