// Autor: Deyan Sanabria Fallas
#include <iostream>
#include <cmath>
#include "time.h"


using std::cout;
using std::endl;
using std::srand;
using std::log10;

void swap(int *a,int *b) {
    int backup = *a;
    *a = *b;
    *b = *a;
}

// Particion con pivote fijo: elije el que esta en el indice mayor
int particionar(int arr[], int min, int max) {

    int pivote = arr[max];
    int i = (min - 1);

    for(int j = min; j <= max - 1; j++) {
        if(arr[j] < pivote) {
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    //cout << "XD" << endl;
    swap(&arr[i+1],&arr[max]);
    return (i+1);
}

// Funcion que cambia el ultimo elemento del array virtual por un elemento
// aleatorio para usarlo como pivote
int pivoteRandom(int arr[], int min, int max) {
    srand(time(0));
    int randomIndex = min + rand() % (max - min);
    swap(&arr[randomIndex],&arr[max]);
    return particionar(arr,min,max);
}

// Esta funcion simplemente esta para incluir el tiempo de la funcion random
// cuando se usa un pivote fijo
int pivoteFijo(int arr[], int min, int max) {
    srand(time(0));
    int randomIndex = min + rand() % (max - min);
    //swap(arr[max],arr[max]);
    return particionar(arr,min,max);
}


void quicksort(int arr[], int min, int max, bool isRandom){
    if(min < max) {
        int pivote;
        if(isRandom) {
            pivote = particionar(arr,min,max);
            
        } else {
            pivote = pivoteRandom(arr,min,max);
        }
        quicksort(arr,min,pivote-1,isRandom);
        quicksort(arr,pivote+1,max,isRandom);
    }
}

void printArray(int arr[], int n){
    cout << "{";
    for(int i = 0; i < n; i++) {
        cout << arr[i];
        if(i != n-1) {
            cout << ",";
        }
    }
    cout << "}" << endl;
}

int main() {
    int *arr = new int[500000];
    for(int i = 0; i < 500000; i++) {
        arr[i] = 500000 - i;
    }
    cout << "hola1" << endl;
    quicksort(arr,0,499999,true);
    cout << "hola" << endl;
    //printArray(arr,29999);
    delete [] arr;
    return 0;
}
