//Creado por: Mauricio Aviles Cisneros
//Modificado por: Deyan Sanabria Fallas y Esteban Perez Picado
#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdexcept>
#include "BSTNode.h"
#include "List.h"
#include "DLinkedList.h"

using std::runtime_error;

template<typename E>
class AVLTree {
private:
    BSTNode<E> *root;
    int size;

    /*
    Aux de insert que agrega un elemento al arbol
    */
    BSTNode<E> *insertAux(BSTNode<E> *current, E element) {
        if(current == nullptr)
            return new BSTNode<E>(element);
        if(element == current->element)
            throw runtime_error("Duplicated element.");
        if(element < current->element) {
            current->left = insertAux(current->left,element);
            return rebalanceLeft(current);
        } else {
            current->right = insertAux(current->right,element);
            return rebalanceRight(current);
        }

    }

    /*
    Balancea el arbol a la izquierda
    */
    BSTNode<E> *rebalanceLeft(BSTNode<E> *current) {
        int leftHeight = height(current->left);
        int rightHeight = height(current->right);
        if(leftHeight - rightHeight > 1) {
            int leftLeftHeight = height(current->left->left);
            int leftRightHeight = height(current->left->right);
            if(leftLeftHeight >= leftRightHeight) {
                // rotacion a la derecha en el abuelo
                return rotateRight(current);
            } else {
                // rotacion a la izquierda en el padre
                // rotacion a la derecha en el abuelo
                current->left = rotateLeft(current->left);
                return rotateRight(current);
            }
        }
        return current;
    }

    /*
    Balancea el arbol a la derecha
    */
    BSTNode<E> *rebalanceRight(BSTNode<E> *current) {
        int leftHeight = height(current->left);
        int rightHeight = height(current->right);
        if(rightHeight - leftHeight > 1) {
            int rightRightHeight = height(current->right->right);
            int rightLeftHeight = height(current->right->left);
            if(rightRightHeight >= rightLeftHeight) {
                // rotacion a la izquierda en el abuelo
                return rotateLeft(current);
            } else {
                // rotacion a la derecha en el padre
                // rotacion a la izquierda en el abuelo
                current->right = rotateRight(current->right);
                return rotateLeft(current);
            }
        }
        return current;
    }

    /*
    calcula la altura de un arbol
    */
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

    /*
    Metodo que rota un arbol a la iquierda
    */
    BSTNode<E> *rotateLeft(BSTNode<E> *current) {
        if(current == nullptr)
            throw runtime_error("Can't rotate left on null.");
        if(current->right == nullptr)
            throw runtime_error("Can't rotate left with null right child.");
        BSTNode<E> *temp = current->right;
        current->right = temp->left;
        temp->left = current;
        return temp;
    }

    /*
    Metodo que rota un arbol a la derecha
    */
    BSTNode<E> *rotateRight(BSTNode<E> *current) {
        if(current == nullptr)
            throw runtime_error("Can't rotate right on null.");
        if(current->left == nullptr)
            throw runtime_error("Can't rotate right with null left child.");
        BSTNode<E> *temp = current->left;
        current->left = temp->right;
        temp->right = current;
        return temp;
    }

    /*
    Aux de find que busca un elemento en el arbol
    */
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

    /*
    Aux de contains que revisa si hay un elemento en el arbol
    */
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

    /*
    Aux del remove que elimina el elemento y mueve el arbol si es necesario
    */
    BSTNode<E> *removeAux(BSTNode<E> *current, E element, E* result) {
        if(current == nullptr)
            throw runtime_error("Element not found.");
        if(element < current->element) {
            current->left = removeAux(current->left, element, result);
            return rebalanceRight(current);
        }
        if(element > current->element) {
            current->right = removeAux(current->right, element, result);
            return rebalanceLeft(current);
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
                return rebalanceLeft(current);
            }
        }
    }

    /*
    Aux de clear que vacia el arbol
    */
    void clearAux(BSTNode<E> *current) {
        if(current==nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    /*
    Aux de getElements que llena la lista.
    */
    void getElementsAux(BSTNode<E> *current, List<E> *elements) {
        if(current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

    /*
    Metodo que obtiene el sucesor  de un nodo
    */
    BSTNode<E> *getSuccesor(BSTNode<E> *current) {
        if(current->left == nullptr)
            return current;
        else
            return getSuccesor(current->left);
    }

    /*
    Metodo que intercambia los valores de dos nodos
    */
    void swap(BSTNode<E> *node1,BSTNode<E> *node2) {
        E element = node1->element;
        node1->element = node2->element;
        node2->element = element;
    }


public:
    // Constructor de la clase
    AVLTree() {
        root = nullptr;
        size = 0;
    }

    // Destructor de la clase
    ~AVLTree() {
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

#endif // AVLTREE_H
