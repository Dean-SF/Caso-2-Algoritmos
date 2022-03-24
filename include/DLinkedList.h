#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include "List.h"
#include "DNode.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename E>
class DLinkedList : public List<E> {
private:
    DNode<E> *head;
    DNode<E> *current;
    DNode<E> *tail;
    int size;

    /*
    Metodo privado checkCurrentElement:
    Revisa si hay elemento actual, de lo contrario manda error
    */
    void checkCurrentElement() {
        if (size == 0)
            throw runtime_error("List is empty");
        if (current->next == tail)
            throw runtime_error("No current element");
    }
public:

    // Constructor de la clase
    DLinkedList() {
        current = head = new DNode<E>(nullptr,nullptr);
        head->next = tail = new DNode<E>(nullptr,head);
        size = 0;
    }
    // Deconstructor de la clase
    ~DLinkedList() {
        clear();
        delete head;
        delete tail;
    }

    /*
    Metodo insert:
    inserta un elemento en la posicion actual
    */
    void insert(E element) {
        current->next = current->next->previous = new DNode<E>(element,current->next,current);
        size++;
    }

    /*
    Metodo append:
    Inserta un elemento en la ultima posicion
    */
    void append(E element) {
        tail->previous = tail->previous->next = new DNode<E>(element,tail,tail->previous);
        size++;
    }

    /*
    Metodo remove:
    Elimina el elemento actual
    */
    E remove() {
        checkCurrentElement();
        E result = current->next->element;
        current->next = current->next->next;
        delete current->next->previous;
        current->next->previous = current;
        size--;
        return result;
    }

    /*
    Metodo clear
    */
    void clear() {
        while(head->next != tail) {
            current = head->next;
            head->next = current->next;
            delete current;
        }
        current = tail->previous = head;
        size = 0;
    }

    /*
    Metodo getElement:
    retorna el elemento actual
    */
    E getElement() {
        checkCurrentElement();
        return current->next->element;
    }

    /*
    Metodo goToStart:
    mueve la posicion actual al inicio de la lista
    */
    void goToStart() {
        current = head;
    }

    /*
    Metodo goToEnd:
    mueve la posicion actual al final de la lista
    */
    void goToEnd() {
        current = tail->previous;
    }

    /*
    Metodo goToPos:
    mueve la posicion actual a un indice indicado
    */
    void goToPos(int pos){
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of range.");
        current = head;
        for (int i = 0; i < pos; i++)
            current = current->next;
    }

    /*
    Metodo next:
    mueve la posicion actual al siguiente
    */
    void next(){
        if (current != tail->previous)
            current = current->next;
    }

    /*
    Metodo previous:
    mueve la posicion actual al anterior
    */
    void previous(){
        if (current != head)
            current = current->previous;
    }

    /*
    Metodo atStart:
    Indica si se esta al inicio de la lista
    */
    bool atStart(){
        return current == head;
    }

    /*
    Metodo atEnd:
    Indica si se esta al final de la lista
    */
    bool atEnd(){
        return current == tail->previous;
    }
    
    /*
    Metodo getPos:
    retorna la posicion actual
    */
    int getPos(){
        int pos = 0;
        for (DNode<E> *temp = head; temp != current; temp = temp->next)
            pos++;
        return pos;
    }

    /*
    Metodo getSize:
    retorna el tamaño de la lista
    */
    int getSize(){
        return size;
    }

    /*
    metodo print:
    Imprime la lista
    */
    void print() {
        DNode<E> *oldCurrent = current;
        cout << "[ ";
        for(goToStart(); !atEnd(); next()) {
            cout << getElement();
            if(!(current->next == tail->previous))
                cout << ", ";
        }
        cout << "]" << endl;
        current = oldCurrent;
    }

    /*
    metodo indexOf:
    retorna el indice de un elemento dado, si no existe, retorna -1
    */
    int indexOf(E element) {
        DNode<E> *oldCurrent = current;                             // se guarda el current para restaurarlo en el futuro
        for(int pos = 0,goToStart(); !atEnd(); next(),pos++) {      // Mediante un for, se recorre toda la lista hasta encontrar
            if (getElement() == element) {                          // el elemento, en caso de que exista, con una posicion contada
                current = oldCurrent;                               // previamente, se retorna pero antes se restaura el current
                return pos;
            }
        }
        current = oldCurrent;                                       // caso de que no exista, se retorna -1 y se restaura el current
        return -1;
    }

    /*
    Metodo contain:
    retorna un booleano dependiendo si un elemento existe en la lista
    */
    bool contains(E element) {
        return indexOf(element) != -1;                  // Se usa el metodo anterior y se comprueba si es distinto de -1
    }                                                   // para de volver true

    /*
    Metodo extend:
    añada los elementos de una lista entrante al final de la lista
    */
    void extend(List<E> *L) {
        int oldPos = L->getPos();
        for(L->goToStart(); !L->atEnd(); L->next()) {   // recorre todos los elementos de la lista entrante 
            this->append(L->getElement());              // y le hace append a cada elemento
        }
        L->goToPos(oldPos);                             // se devuelve la posicion que tenia antes de alterarla
    }
    
    /*
    Metodo extend:
    añada los elementos de una lista entrante al final de la lista
    */
    bool equals(List<E> *L) {
        int oldPosEntrada = L->getPos();                                                // Se guardan la posiciones actuales de las listas
        DNode<E> *oldCurrent = current;
        for(goToStart(),L->goToStart(); !atEnd() || !L->atEnd(); next(),L->next()) {    // Con un for se manda ambas listas a su inicio.
            if (L->getElement() != getElement()) {                                      // se cambia de elemento en cada ciclo,
                L->goToPos(oldPosEntrada);                                              // y se comprueba si alguna lista llego al final
                current = oldCurrent;                                                   // si algun elemento no cuadra se retorna false
                return false;                                                           // y se restauran las posiciones
            }
        }
        L->goToPos(oldPosEntrada);                                                      // Si no, se devuelve true y se restauran las posiciones
        current = oldCurrent;
        return true;
    }

};

#endif