#include <iostream>
#include <string>
#include <fstream>
#include "time.h"
#include "include/Trie.h"

using std::cout;
using std::endl;
using std::istream;
using std::getline;


// Algoritmo que abre el archivo y carga palabras (que contengan solo letras del abecedario anglosajon) en un
// Trie Tree para su analisis
bool loadFileOptimize(Trie *container,string fileName) {
    string palabra = "";
    char character;
    ifstream file;
    fileName = "./textos/" + fileName;
    file.open(fileName);
    if(!file.is_open()) {
        return false;
    }
    while(file.get(character)) {
        if(65 <= character && character <= 90) {
            palabra += (character+32);
        }else if(97 <= character && character <= 122) {
            palabra += character;
        } else if (!palabra.empty()) {
            container->insert(palabra);
            palabra = "";
        }
    }
    return true;
}


int main() {
    Trie words;
    const string FILENAME = "textoPrueba.txt"; // colocar aqui el nombre del archivo que se debe encontrar en la carpeta "textos"
                                               // con extension

    const string WORDTOFIND = "name"; // Nombre de la palabra a buscar
    cout << "--------- ANALIZANDO ARCHIVO ---------" << endl << endl;
    clock_t time = clock();
    if(!loadFileOptimize(&words,FILENAME)) {
        cout << "ERROR: No se ha encontrado el archivo" << endl;
        return 0;
    }
    time = clock() - time;

    cout << "Carga de archivo duro: " << time << " ticks" << endl << endl;

    time = clock();
    List<string> *matches = words.getMatches(WORDTOFIND);
    time = clock() - time;

    matches->print();
    cout << endl << "Encontrar palabras se tardo (sin print): " << time << " ticks" << endl << endl;

    time = clock();
    cout << "la palabra " << WORDTOFIND << " aparece: " << words.prefixCount(WORDTOFIND) << endl;
    time = clock() - time;
    cout << endl << "Encontrar apariciones : " << time << " ticks" << endl;

    return 0;
}
