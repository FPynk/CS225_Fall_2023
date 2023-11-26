#include "sketching.h"

#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <iostream>

std::vector<uint64_t> kminhash(std::vector<int> inList, unsigned k, hashFunction h) {
    std::set<uint64_t> hash_vals;
    std::vector<uint64_t> min_hashes;
    // Cycle thru inList
    for (int i : inList) {
        // Apply Hash
        // Store vals in set (auto sorted) (use this to figure out what index to max int after)
        hash_vals.insert(h(i));
    }
    // Fill hash vec with min vals
    auto it = hash_vals.begin();
    for (unsigned int i = 0; i < k && it != hash_vals.end(); ++i, ++it) {
        min_hashes.push_back(*it);
    }
    // Fill up missing with GLOBAL_MAX_INT
    while (min_hashes.size() < k) {
        min_hashes.push_back(GLOBAL_MAX_INT);
    }
    return min_hashes;
}

std::vector<uint64_t> khash_minhash(std::vector<int> inList, std::vector<hashFunction> hv) {
    // store output vector
    std::vector<uint64_t> output;
    // Cycle thru each hash function
    for (auto& hash : hv) {
        // Cycle thru each int
        uint64_t min_hash_val = UINT64_MAX;
        for (int i : inList) {
            // Record min vals outputted from hash
            uint64_t val = hash(i);
            if (min_hash_val > val) {
                min_hash_val = val;
            }
        }
        // take min and store that 
        output.push_back(min_hash_val);
    }
    return output;
}

std::vector<uint64_t> kpartition_minhash(std::vector<int> inList, int part_bits, hashFunction h) {
    // calc no of parts: 2^n
    size_t num_parts = std::pow(2, part_bits);
    // Create vector for each partition min, init to all max
    std::vector<uint64_t> output(num_parts, GLOBAL_MAX_INT);
    // Cycle thru inlist and hash
    for (int i : inList) {
        // For each hash, determine partition and store if min
        uint64_t hash_val = h(i);

        // figure out partition
        // right shift to align part bits and then mask with a 0111...
        size_t part = (hash_val >> (64 - part_bits)) & ((1 << part_bits) - 1);

        // update min val
        if (hash_val < output[part]) {
            output[part] = hash_val;
        }
    }

    return output;
}

float minhash_jaccard(std::vector<uint64_t> mh1, std::vector<uint64_t> mh2) {
    // J = intersection / union
    float intersection = 0.0;
    float union_num = 0.0;
    std::vector<uint64_t> union_vec;
    // loop thru mh1 and count int, form union at same time
    // check valid val
    for (uint64_t i1 : mh1) {
        if (i1 != GLOBAL_MAX_INT) {
            if (std::find(mh2.begin(), mh2.end(), i1) != mh2.end()) {
                intersection++;
            }
            if (std::find(union_vec.begin(), union_vec.end(), i1) == union_vec.end()) {
                union_vec.push_back(i1);
            }
        }
    }
    // adding leftover mh2 vals to union
    for (uint64_t i2 : mh2) {
        if (i2 != GLOBAL_MAX_INT && std::find(union_vec.begin(), union_vec.end(), i2) == union_vec.end()) {
            union_vec.push_back(i2);
        }
    }
    union_num = union_vec.size();
    float result = union_num == 0 ? 0.0 : intersection / union_num;
    return result;
}

int minhash_cardinality(std::vector<uint64_t> mh, unsigned k) {
    if (mh.empty() || k == 0 || k > mh.size()) {
        return 0; // invalid input
    }
    // grab kth minhash
    uint64_t kth_min_val = mh[k-1];
    if (kth_min_val == GLOBAL_MAX_INT) {
        return 0; // kth min hash shouldnt be place holder
    }
    // uint64_t max = *std::max_element(mh.begin(), mh.end());
    // calc caridnality and round up
    //std::cout << "k " << k << std::endl;
    //std::cout << "kth_min_val " << kth_min_val << std::endl;
    //std::cout << "max " << max << std::endl;
    //std::cout << "UINT64_MAX " << UINT64_MAX << std::endl;
    double normalised = (static_cast<double>(kth_min_val) / static_cast<double>(UINT64_MAX));
    //std::cout << "normalised " << normalised << std::endl;
    double card = std::ceil((k / normalised) - 1);
    return static_cast<int>(card);
}


float exact_jaccard(std::vector<int> raw1, std::vector<int> raw2) {
    return 0.0;
}

int exact_cardinality(std::vector<int> raw) {
    return 0;
}

MM::MM(const cs225::PNG& input, unsigned numTiles, unsigned k, hashFunction h) {
}


std::vector<uint64_t> MM::getMinHash(unsigned width, unsigned height) const {
    return std::vector<uint64_t>();
}

int MM::countMatchTiles(const MM & other, float threshold) const {
    return 0;
}

std::vector<std::tuple<int, int, int>> build_minhash_graph(std::vector<std::string> flist, unsigned numTiles, unsigned k, hashFunction h, float threshold) {
    return std::vector<std::tuple<int, int, int>>();
}