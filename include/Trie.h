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
    
    /*
    Dado un prefijo, busca todas las palabras con ese prefijo de forma
    recursiva
    */
    void getMatchesAux(TrieNode* current, string prefix, List<string>* words){
        if(current->isFinal)
            words->append(prefix);
        List<char> *children = current->getChildren();
        for(children->goToStart(); !children->atEnd(); children->next()){
            char c = children->getElement();
            string newPrefix = prefix;
            newPrefix.append(1,c);
            getMatchesAux(current->getChild(c), newPrefix, words);
        }
        delete children;
    }

    /*
    Metodo de limpieza del trie recursivo, hasta que no queda nada
    devuelve la memoria al sistema
    */
    void clearAux(TrieNode *current){
        List<TrieNode*> *pointers = current->getChildrenPointers();
        for(pointers->goToStart(); !pointers->atEnd(); pointers->next()){
            clearAux(pointers->getElement());
        }
        delete current;
    }


public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        clear();
        delete root;
    }

    /*
    Elimina todos los contenidos del trie
    */
    void clear(){
        clearAux(root);
        root = new TrieNode();
    }

    /*
    Retorna una lista con todas las palabras que coincidan con
    el prefijo
    */
    List<string>* getMatches(string prefix){
        List<string> *words = new DLinkedList<string>();
        TrieNode *current = root;
        for(unsigned int i = 0; i<prefix.size(); i++){
            if(!current->contains(prefix[i]))
                return words;
            current = current->getChild(prefix[i]);
        }
        getMatchesAux(current, prefix, words);
        return words;
    }

    /*
    Metodo para meter un elemento dentro del trie
    */
    void insert(string word) {
        /*
        if(containsWord(word))
            throw runtime_error("Word already in trie.");
        */
        
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

    /*
    Metodo que busca si una palabra esta dentro
    del trie
    */
    bool containsWord(string word) {
        TrieNode *current = root;
        for(unsigned int i = 0; i < word.size(); i++) {
            if(!current->contains(word[i]))
                return false;
            current = current->getChild(word[i]);
        }
        return current->isFinal;
    }

    /*
    Metodo que revisa si contiene un prefijo
    */
    bool containsPrefix(string prefix) {
        TrieNode *current = root;
        for(unsigned int i = 0; i < prefix.size(); i++) {
            if(!current->contains(prefix[i]))
                return false;
            current = current->getChild(prefix[i]);
        }
        return true;
    }

    /*
    retorna la cantidad de palabras que contiene este prefijo
    */
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