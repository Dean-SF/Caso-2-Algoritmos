#include <iostream>
#include "time.h"
#include <cmath>

using std::cout;
using std::endl;
using std::pow;

void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
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
    const int SIZE_CUADRATIC = 5000;
    const int SIZE_LINEAR = 2000000;
    const int TEST_COUNT = 10;
    int arrSize = SIZE_CUADRATIC;
    int time[TEST_COUNT];
    
    cout << "--- --- --- TEST CASO CUADRATICO --- --- ---" << endl;

    for(int j = 0; j < TEST_COUNT; j++) {
        int *arr = new int[arrSize];
        for(int i = 0; i < arrSize; i++) {
            arr[i] = arrSize - i;
        }
        clock_t t = clock();
        insertionSort(arr,arrSize);
        t = clock() - t;
        time[j] = t;
        cout << "Para " << arrSize << " elementos: " << t << " ticks" << endl;
        delete [] arr;
        arrSize += SIZE_CUADRATIC;
    }
    cout << endl << "los resultados anteriores pueden compararse con la funcion: ";
    cout << "f(x) = " << time[0] << "x^2 -> la cual es cuadratica" << endl;
    cout << "Tasas de Crecimiento:" << endl;
    for(int i = 0; i < TEST_COUNT - 1; i++) {
        cout << "T" << i+1 << " " << time[i+1] - time[i];
        cout << "   F" << i+1 << " " << time[0]*pow(i+2,2) - time[0]*pow(i+1,2) << endl;
    }

    cout << endl << "Se puede apreciar que en este caso, el cual es usar el insertion sort para ordenar " << endl;
    cout << "elementos que estan en el orden inverso, tiene una compejidad de tiempo O(n^2), puesto que si" << endl;
    cout << "se compara con una funcion cuadratica, tiende a tener una tasa de crecimiento parecida," << endl;
    cout << "dicha tasa de crecimiento tiende a variar por el sistema operativo y los programas en ejecucion," << endl;
    cout << "asi que tiendo eso en consideracion se puede concluir que para este caso el insertionSort() tiene" << endl;
    cout << "una complejidadd de O(n^2)" << endl;

    cout << endl << "--- --- --- TEST CASO LINEAL --- --- ---" << endl;

    arrSize = SIZE_LINEAR;
    for(int j = 0; j < TEST_COUNT; j++) {
        int *arr = new int[arrSize];
        for(int i = 0; i < arrSize; i++) {
            arr[i] = i;
        }
        clock_t t = clock();
        insertionSort(arr,arrSize);
        t = clock() - t;
        time[j] = t;
        cout << "Para " << arrSize << " elementos: " << t << " ticks" << endl;
        delete [] arr;
        arrSize += SIZE_LINEAR;
    }
    cout << endl << "los resultados anteriores pueden compararse con la funcion: ";
    cout << "f(x) = " << time[0] << "x -> la cual es lineal" << endl;
    cout << "Tasas de Crecimiento:" << endl;
    for(int i = 0; i < TEST_COUNT - 1; i++) {
        cout << "T" << i+1 << " " << time[i+1] - time[i];
        cout << "   F" << i+1 << " " << time[0]*(i+2) - time[0]*(i+1) << endl;
    }

    cout << endl << "Para este caso, el algoritmo insertionSort() esta intentando ordenar un arreglo" << endl;
    cout << "que ya se encuentra previamente ordenado, por lo que solo recorre el array \"n\" veces, lo que" << endl;
    cout << "teoricamente brinda una complejidad temporal lineal. Para los tests anteriores se puede apreciar" << endl;
    cout << "que las tasas de crecimiento no varian demasiado para el algoritmo, estas variaciones se pueden tomar" << endl;
    cout << "como variaciones causada por procesos en segundo plano y el sistema operativo, ademas que no suelen" << endl;
    cout << "variar demasiado y tienen cierta tendencia a la tasa de crecimiento de la funcion lineal presentada." << endl;
    cout << "Se puede concluir que la compejidad temporal del algoritmo para este caso es lineal O(n)" << endl;
    cout << "" << endl;

    return 0;
}
