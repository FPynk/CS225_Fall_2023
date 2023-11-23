/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include "bloom.h"
 #include <algorithm>

BF::BF(uint64_t size, std::vector<hashFunction> hashList){
    // Your code here 
    hv = hashList;
    bv = std::vector<bool>(size, false);
}

BF::BF(const BF& other){
    // Your code here 
    hv = other.hv;
    bv = other.bv;
}

BF::~BF(){
    return;
}

void BF::add(const int & key){
    // Your code here
    for (auto& hf : hv) {
        int idx = hf(key) % bv.size();
        bv[idx] = true;
    }
}

bool BF::contains(const int& key) const{
    // Your code here 
    for (auto& hf : hv) {
        int idx = hf(key) % bv.size();
        // zero found
        if (bv[idx] == false) {
            return false;
        }
    }
    return true;
}

void BF::bit_union(const BF& other){
    // Your code here 
    // assuming both BFs have same size and hashes, not checking
    // loop thru each bit
    for (unsigned int i = 0; i < bv.size(); ++i) {
        // check 1 bit present in either
        if (bv[i] || other.bv[i]) {
            bv[i] = 1;
        }
    }
}

void BF::intersect(const BF& other){
    // Your code here 
    // assuming both BFs have same size and hashes, not checking
    // loop thru each bit
    for (unsigned int i = 0; i < bv.size(); ++i) {
        // check 1 bit present in both
        if (bv[i] && other.bv[i]) {
            bv[i] = 1;
        } else {
            bv[i] = 0;
        }
    }
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){
    // Your code here
    BF bf = BF(size, hashList);
    for (int i : inList) {
        bf.add(i);
    }
    int TN = 0;
    int FP = 0;
    // Check every number from 0 to max - 1
    for (unsigned int i = 0; i < max; ++i) {
        // Check if the number is in the bloom filter
        bool isInBloomFilter = bf.contains(i);

        // Check if the number is in the input list
        bool isInList = std::find(inList.begin(), inList.end(), i) != inList.end();

        // Count false positives and true negatives
        if (isInBloomFilter && !isInList) {
            ++FP;
        } else if (!isInBloomFilter) {
            ++TN;
        }
    }

    return static_cast<float>(FP) / (TN + FP);
}

bool contains(std::vector<int> inList, unsigned int i) {
    for (int j : inList) {
        if (j == static_cast<int>(i)) {
            return true;
        }
    }
    return false;
}

bool getBitFromArray(std::vector<char> bv, int index) {
    if (index < 0 || index >= static_cast<int>(bv.size() * 8)) {
        // Handle out-of-range index
        return false;
    }

    int byteIndex = index / 8; // Find the byte containing the bit
    int bitIndex = index % 8;  // Find the position of the bit within the byte

    // Use getBitFromByte to extract the bit
    return getBitFromByte(bv[byteIndex], bitIndex);
}

bool getBitFromByte(char in, int index){
    // Your code here
    // since its 0 indexed from left to right instead of right to left
    int shift = 7 - index;
    int bitmask = 1 << shift;

    return (in & bitmask) != 0;
}

