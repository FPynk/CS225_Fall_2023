#include "sketching.h"
#include "../lib/cs225/BWPixel.h"
#include "../lib/cs225/PNG.h"

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

/**
 * Given two raw datasets containing a vector of integers, compute the exact Jaccard similarity between datasets.
 * Your similarity metric must ignore duplicates present in the dataset when computing the relevant cardinalities.
 * In other words, treat your input as two sets and do a set comparison.
 *  
 * @param raw1 The first dataset being compared
 * @param raw2 The second dataset being compared
 * @return A float between 0 and 1 (inclusive) storing the actual similarity between datasets
 */

float exact_jaccard(std::vector<int> raw1, std::vector<int> raw2) {
    // fuck you DUPLICATESSSSSSSSSS
    std::set<int> set1(raw1.begin(), raw1.end());
    std::set<int> set2(raw2.begin(), raw2.end());
    // setup for union and intersection
    std::set<int> union_set;
    std::vector<int> intersect;
    
    // intersection
    // notes for future andrew
    // set1 and set2 must be sorted, auto done for std::set
    // last argument is the otput iterator to beginning of a range to store the results
    // , in this case back_inserter returns insert iterator that uses push_back function of a container (vector)
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(intersect));

    // union stuff
    union_set.insert(set1.begin(), set1.end());
    union_set.insert(set2.begin(), set2.end());

    float result = union_set.empty() ? 0.0 : static_cast<float>(intersect.size())/ static_cast<float>(union_set.size());    
    return result;
}

int exact_cardinality(std::vector<int> raw) {
    std::set<int> set(raw.begin(), raw.end());
    return set.size();
}

MM::MM(const cs225::PNG& input, unsigned numTiles, unsigned k, hashFunction h) : numTiles_(numTiles) {
    // calcing tile dims
    // rmmbr to account for when pix gets cut off
    std::cout << "PNG Dimensions: X*Y " << input.width() << "*" << input.height();
    unsigned int tile_width = std::ceil(static_cast<double>(input.width()) / numTiles);
    unsigned int tile_height = std::ceil(static_cast<double>(input.height()) / numTiles);
    std::cout << " numTiles: " << numTiles << " | tile_width: " << tile_width << " tile_height " << tile_height << std::endl; 
    minHashes_ = std::vector<std::vector<uint64_t>>(numTiles * numTiles);
                
    // loop thru tiles
    for (unsigned int i = 0; i < numTiles; ++i) {
        for (unsigned int j = 0; j < numTiles; ++j) {
            unsigned int start_x = j * tile_width;
            unsigned int start_y = i * tile_height;
            // account for uneven sized tiles
            unsigned int end_x = std::min(start_x + tile_width, input.width());
            unsigned int end_y = std::min(start_y + tile_height, input.height());
            // min hash vec and input vec
            std::vector<uint64_t> tile_min_hashes_vec;
            std::vector<int> inList = std::vector<int>();
            // fill up input vec
            for (unsigned int y = start_y; y < end_y; ++y) {
                for (unsigned int x = start_x; x < end_x; ++x) {
                    const BWPixel & pix = input.getPixel(x, y);
                    // get an int from the pix for hashing
                    int pix_val = static_cast<int>(pix.l * 255);
                    inList.push_back(pix_val);
                }
            }
            // hash input vec and store
            tile_min_hashes_vec = kminhash(inList, k, h);
            minHashes_[i*numTiles + j] = tile_min_hashes_vec;
        }
    }
}


std::vector<uint64_t> MM::getMinHash(unsigned width, unsigned height) const {
    // unsigned int x_tile = width / tile_width_;
    // unsigned int y_tile = height / tile_height_;
    return minHashes_[height * numTiles_ + width];
}

int MM::countMatchTiles(const MM & other, float threshold) const {
    int count = 0;
    // assuming same tile dimensions for both
    for (unsigned int i = 0; i < numTiles_; ++i) {
        for (unsigned int j = 0; j < numTiles_; ++j) {
            if (minhash_jaccard(minHashes_[i*numTiles_ + j], other.getMinHash(j, i)) >= threshold) {
                count++;
            }
        }
    }
    return count;
}

std::vector<std::tuple<int, int, int>> build_minhash_graph(std::vector<std::string> flist, unsigned numTiles, unsigned k, hashFunction h, float threshold) {
    std::vector<std::tuple<int, int, int>> edge_vec;
    
    // vec to store minhash per image
    std::vector<MM> minHash_vec;

    // convert image in flist to minhash then store
    for (const std::string& filename: flist) {
        cs225::PNG png;
        png.readFromFile(filename);
        MM mm(png, numTiles, k, h);
        minHash_vec.push_back(mm);
    }

    // pairwise comparison, i think this works idk
    for (size_t i = 0; i < minHash_vec.size(); ++i) {
        for (size_t j = i + 1; j < minHash_vec.size(); ++j) {
            int matching_tiles = minHash_vec[i].countMatchTiles(minHash_vec[j], threshold);
            edge_vec.emplace_back(i, j, matching_tiles);
        }
    }

    return edge_vec;
}