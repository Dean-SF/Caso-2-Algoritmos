#ifndef TRIENODE_H
#define TRIENODE_H

#include "AVLTreeDictionary.h"

class TrieNode {
private:
    AVLTreeDictionary<char,TrieNode*> children;
    
public:
    bool isFinal;
    int prefixCount;



    TrieNode() : children() {
        isFinal = false;
        prefixCount = 0;
    }
    ~TrieNode() {}

    bool contains(char c) {
        return children.contains(c);
    }

    void add(char c) {
        TrieNode *newNode = new TrieNode();
        children.insert(c,newNode);
    }

    void remove(char c) {
        // Puede ser que este delete haya que quitarlo
        delete children.remove(c);
    }

    TrieNode *getChild(char c) {
        return children.getValue(c);
    }

    List<char> *getChildren() {
        return children.getKeys();
    }

    List<TrieNode*> *getChildrenPointers() {
        return children.getValues();
    }

};

#endif