#include "sketching.h"

#include <vector>
#include <set>

/**
 * Given a list of integers (possibly with repeated values) and a hash function, return a list containing the k-minimum hash values.
 * If you generate the same hash value twice, you should only track it once for the purposes of recording minima.
 * Your final return vector should be ordered from smallest to largest starting with the global min. 
 * In other words, the 1st minimum value should be stored at index 0 (and the k-th minimum at index k-1). 
 * 
 * HINT: You are free to use your previous assignments to build a way of tracking k minimum values.
 *
 * NOTE: If there arent enough unique hash values in the input set, you should use GLOBAL_MAX_INT to fill in the
 * remaining positions. This is the only allowable duplicate. 
 *  
 * @param inList A vector of integers to be run through minhash
 * @param k An unsigned integer describing the number of minima that need to be tracked (and returned)
 * @param h An hash function that takes in an integer and returns a uint64_t
 * @return A vector of uint64_t containing the k-min hash values using one hash
 */

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
    return std::vector<uint64_t>();
}

std::vector<uint64_t> kpartition_minhash(std::vector<int> inList, int part_bits, hashFunction h) {
    return std::vector<uint64_t>();
}

float minhash_jaccard(std::vector<uint64_t> mh1, std::vector<uint64_t> mh2) {
    return 0.0;
}

int minhash_cardinality(std::vector<uint64_t> mh, unsigned k) {
    return 0;
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