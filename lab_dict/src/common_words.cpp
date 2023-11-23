/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;
using std::set;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        [](int c) {return std::ispunct(c);});
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());
    //std::cout << "file_word_maps " << file_word_maps.size() << std::endl;

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        //std::cout << "ran " << i << std::endl;
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        map<string, unsigned int> freq;
        /* Your code goes here! */
        for (string word: words) {
            //std::cout << "word: " << word << std::endl;
            if (freq.find(word) == freq.end()) {
                freq[word] = 1;
            } else {
                freq[word]++;
            }
        }
        file_word_maps[i] = freq;
    }
    //std::cout << "file_word_maps " << file_word_maps.size() << std::endl;
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    for (const auto& wordMap : file_word_maps) {
        std::set<std::string> wordsInCurrentFile;

        for (const auto& wordPair : wordMap) {
            const std::string& word = wordPair.first;
            wordsInCurrentFile.insert(word);
        }

        for (const auto& word : wordsInCurrentFile) {
            //std::cout << "common[word]: " << word << " " << common[word] + 1 << std::endl;
            common[word]++;
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    for (const auto& wordPair : common) {
        //std::cout << "wordPair.second " << wordPair.second << " file_word_maps.size() " << file_word_maps.size() << std::endl;
        if (wordPair.second == file_word_maps.size()) {
            string word = wordPair.first;
            bool isCommon = true;
            for (const map<string, unsigned int>& wordMap : file_word_maps) {
                //std::cout << "word " << word << " at " << wordMap.at(word) << std::endl;
                if (wordMap.at(word) < n) {
                    isCommon = false;
                    break;
                }
            }
            if (isCommon) {
                out.push_back(word);
                //std::cout << word << std::endl;
            }
        }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
