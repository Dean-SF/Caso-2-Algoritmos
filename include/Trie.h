#ifndef TRIE_H
#define TRIE_H
#include "TrieNode.h"
#include <stdexcept>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

class Trie {
private:
    TrieNode *root;
    
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        //clear();
        delete root;
    }

    void insert(string word) {
        if(containsWord(word))
            throw runtime_error("Word already in trie.");
        TrieNode *current = root;
        for(unsigned int i = 0; i < word.size(); i++) {
            current->prefixCount++;
            if(!current->contains(word[i]))
                current->add(word[i]);
            current = current->getChild(word[i]);
        }
        current->prefixCount++;
        current->isFinal = true;
    }

    bool containsWord(string word) {
        TrieNode *current = root;
        for(unsigned int i = 0; i < word.size(); i++) {
            if(!current->contains(word[i]))
                return false;
            current = current->getChild(word[i]);
        }
        return current->isFinal;
    }

    bool containsPrefix(string prefix) {
        TrieNode *current = root;
        for(unsigned int i = 0; i < prefix.size(); i++) {
            if(!current->contains(prefix[i]))
                return false;
            current = current->getChild(prefix[i]);
        }
        return true;
    }

    int prefixCount(string prefix) {
        TrieNode *current = root;
        for(unsigned int i = 0; i < prefix.size(); i++) {
            if(!current->contains(prefix[i]))
                return false;
            current = current->getChild(prefix[i]);
        }
        return current->prefixCount;
    }
};

#endif