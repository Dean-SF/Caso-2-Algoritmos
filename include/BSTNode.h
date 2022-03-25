//Creado por: Mauricio Aviles Cisneros
//Modificado por: Deyan Sanabria Fallas y Esteban Perez Picado
#ifndef BSTNODE_H
#define BSTNODE_H

template<typename E>
class BSTNode{
public:
    E element;
    BSTNode<E> *left;
    BSTNode<E> *right;

    /*
    Contructor del nodo con el elemento y los dos punteros
    */
    BSTNode(E element, BSTNode<E> *left = nullptr, BSTNode<E> *right = nullptr) {
        this->element = element;
        this->left = left;
        this->right =  right;
    }

    /*
    Verifica si el nodo es hoja y retorna true o false
    */
    bool isLeaf() {
        return left == nullptr && right == nullptr;
    }

    /*
    Metodo que cuenta la cantidad de los hijos del nodo
    */
    int childrenCount() {
        return (left == nullptr? 0 : 1) + (right == nullptr? 0 : 1);
    }

    /*
    Metodo que retorna el hijo unico del nodo
    */
    BSTNode<E> *getUniqueChild() {
        return left == nullptr? right : left;
    }

};

#endif // BSTNODE_H
