//Creado por: Mauricio Aviles Cisneros
//Modificado por: Deyan Sanabria Fallas
#ifndef AVLTREEDICTIONARY_H
#define AVLTREEDICTIONARY_H
#include "Dictionary.h"
#include "AVLTree.h"
#include "KVPair.h"
#include "List.h"
#include "DLinkedList.h"

template<typename K, typename V>
class AVLTreeDictionary : public Dictionary<K,V>{
private:
    AVLTree<KVPair<K,V>> elements;

public:
    // Constructor default de la clase
    AVLTreeDictionary() {}

    // Destructor de la clase
    ~AVLTreeDictionary() {}

    /*
    Metodo insert: inserta un par llave-valor al diccionario
    */
    void insert(K key, V value) {
        KVPair<K,V> p(key,value);
        elements.insert(p);
    }

    /*
    Metodo remove: Elimina un par del diccionario dada la llave
    */
    V remove(K key) {
        KVPair<K,V> p(key);
        p = elements.remove(p);
        return p.value;
    }

    /*
    Metodo getValue: retorna el valor de una llave
    */
    V getValue(K key) {
        KVPair<K,V> p(key);
        p = elements.find(p);
        return p.value;
    }

    /*
    Metodo setValue: cambia el valor de una llave
    */
    void setValue(K key, V value) {
        KVPair<K,V> p(key,value);
        elements.remove(p);
        elements.insert(p);
    }

    /*
    Metodo contains: retorna true cuando existe un elemento
    con la llave dada, de lo contrario retorna false
    */
    bool contains(K key) {
        KVPair<K,V> p(key);
        return elements.contains(p);
    }

    /*
    Metodo getKeys: retorna una lista con todas las llaves
    */
    List<K> *getKeys() {
        List<K> *keys = new DLinkedList<K>();
        List<KVPair<K,V>> *pairs = elements.getElements();
        for(pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K,V> p = pairs->getElement();
            keys->append(p.key);
        }
        delete pairs;
        return keys;
    }

    /*
    Metodo getValues: retorna una lista con todos los valores
    */
    List<V> *getValues() {
        List<V> *values = new DLinkedList<V>();
        List<KVPair<K,V>> *pairs = elements.getElements();
        for(pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K,V> p = pairs->getElement();
            values->append(p.value);
        }
        delete pairs;
        return values;
    }

    /*
    Metodo getSize: retorna el tamaño del diccionario
    */
    int getSize() {
        return elements.getSize();
    }

    /*
    Metodo clear: borra todos los elementos del diccionario
    */
    void clear() {
        elements.clear();
    }

    /*
    Metodo print: Imprime todo el diccionario
    */
    void print() {
        cout << "{ ";
        List<KVPair<K,V>> *pairs = elements.getElements();
        for(pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            cout << pairs->getElement() << ", ";
        }
        cout << "}\n";
    }

    /*
    Metodo zip: añade pares juntando dos listas al diccionario
    */
    void zip(List<K> *keys, List<V> *values) {
        keys->goToStart();
        values->goToStart();
        while (!keys->atEnd() && !values->atEnd()) {
            K kActual = keys->getElement();
            V vActual = values->getElement();

            if(elements.contains(kActual))
                setValue(kActual,vActual);
            else
                insert(kActual,vActual);

            keys->next();
            values->next();
        }
    }

    /*
    Metodo update: añade pares de otro diccionario en el actual
    */
    void update(Dictionary<K, V> *D) {
        List<V> *values = D->getValues();
        List<K> *keys = D->getKeys();
        zip(keys,values);
    }


};


#endif // AVLTREEDICTIONARY_H
