#ifndef BSTREE_H
#define BSTREE_H
#include <stdexcept>
#include "BSTNode.h"
#include "List.h"
#include "DLinkedList.h"

using std::runtime_error;

template<typename E>
class BSTree {
private:
    BSTNode<E> *root;
    int size;

    BSTNode<E> *insertAux(BSTNode<E> *current, E element) {
        if(current == nullptr)
            return new BSTNode<E>(element);
        if(element == current->element)
            throw runtime_error("Duplicated element.");
        if(element < current->element) {
            current->left = insertAux(current->left,element);
            return current;
        } else {
            current->right = insertAux(current->right,element);
            return current;
        }
        
    }

    int height(BSTNode<E> *current) {
        if(current == nullptr) 
            return 0;
        int leftHeight = height(current->left);
        int rightHeight = height(current->right);
        if(leftHeight > rightHeight)
            return 1 + leftHeight;
        else
            return 1 + rightHeight;
    }

    E findAux(BSTNode<E> *current, E element) {
        if(current == nullptr)
            throw runtime_error("Element not found.");
        if(element == current->element)
            return current->element;
        if(element < current->element)
            return findAux(current->left,element);
        else
            return findAux(current->right,element);
    }

    bool containsAux(BSTNode<E> *current, E element) {
        if(current == nullptr)
            return false;
        if(element == current->element)
            return true;
        if(element < current->element)
            return containsAux(current->left,element);
        else
            return containsAux(current->right,element);
    }

    BSTNode<E> *removeAux(BSTNode<E> *current, E element, E* result) {
        if(current == nullptr)
            throw runtime_error("Element not found.");
        if(element < current->element) {
            current->left = removeAux(current->left, element, result);
            return current;
        }
        if(element > current->element) {
            current->right = removeAux(current->right, element, result);
            return current;
        } else { // element == current->element
            *result = current->element;
            if(current->isLeaf()) {
                delete current;
                return nullptr;
            }
            if(current->childrenCount() == 1) {
                BSTNode<E> *child = current->getUniqueChild();
                delete current;
                return child;
            } else { // el nodo tiene dos hijos
                BSTNode<E> *succesor = getSuccesor(current->right);
                swap(current,succesor);
                current->right = removeAux(current->right,element,result);
                return current;
            }
        }
    }

    void clearAux(BSTNode<E> *current) {
        if(current==nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    void getElementsAux(BSTNode<E> *current, List<E> *elements) {
        if(current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

    BSTNode<E> *getSuccesor(BSTNode<E> *current) {
        if(current->left == nullptr)
            return current;
        else
            return getSuccesor(current->left);
    }

    void swap(BSTNode<E> *node1,BSTNode<E> *node2) {
        E element = node1->element;
        node1->element = node2->element;
        node2->element = element;
    }


public:
    // Constructor de la clase
    BSTree() {
        root = nullptr;
        size = 0;
    }

    // Destructor de la clase
    ~BSTree() {
        clear();
    }

    /*
    Metodo insert: inserta un elemento dentro del arbol
    */
    void insert(E element) {
        root = insertAux(root,element);
        size++;
    }

    /*
    Metodo find: encuentra un elemento en el arbol y
    lo retorna
    */
    E find(E element) {
        return findAux(root,element);
    }

    /*
    Metodo contains: Retorna true si el arbol encuentra el
    elemento a buscar y false en caso contrario
    */
    bool contains(E element) {
        return containsAux(root,element);
    }

    /*
    Metodo remove: remueve un elemento del arbol
    */
    E remove(E element) {
        E result;
        root = removeAux(root, element, &result);
        size--;
        return result;
    }

    /*
    Metodo Clear: borra todos los contenidos del arbol
    */
    void clear() {
        clearAux(root);
        root = nullptr;
        size = 0;
    }

    /*
    Metodo getElements: retorna un puntero a lista con todos 
    los elementos del arbol
    */
    List<E> *getElements() {
        List<E> *elements = new DLinkedList<E>();
        getElementsAux(root,elements);
        return elements;
    }

    /*
    Metodo getSize: retorna el tamaño del arbol
    */
    int getSize() {
        return size;
    }

    /*
    Metodo height: retorna la altura del arbol
    */
    int height() {
        return height(root);
    }

};

#endif // BSTREE_H
