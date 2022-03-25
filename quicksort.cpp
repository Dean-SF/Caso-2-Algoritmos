// Autor: Deyan Sanabria Fallas
#include <iostream>
#include <cmath>
#include "time.h"


using std::cout;
using std::endl;
using std::swap;

// Particion con pivote fijo: elije el que esta en el indice mayor
int particionar(int arr[], int min, int max) {

    int pivote = arr[max];
    int i = (min - 1);

    for(int j = min; j <= max - 1; j++) {
        if(arr[j] < pivote) {
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[max]);
    return (i+1);
}

// Funcion que cambia el ultimo elemento del array virtual por un elemento
// aleatorio para usarlo como pivote
int pivoteRandom(int arr[], int min, int max) {
    srand(time(0));
    int randomIndex = min + rand() % (max - min);
    swap(arr[randomIndex],arr[max]);
    return particionar(arr,min,max);
}

// Esta funcion simplemente esta para incluir el tiempo de la funcion random
// cuando se usa un pivote fijo y se use el de mas a la derecha
int pivoteFijoDerecha(int arr[], int min, int max) {
    srand(time(0));
    int randomIndex = min + rand() % (max - min);
    swap(arr[max],arr[max]);
    return particionar(arr,min,max);
}

void quicksort(int arr[], int min, int max, bool isRandom){
    if(min < max) {
        int pivote;
        if(isRandom) {
            pivote = pivoteRandom(arr,min,max);
        } else {
            pivote = pivoteFijoDerecha(arr,min,max);
        }
            
        quicksort(arr,min,pivote-1,isRandom);
        quicksort(arr,pivote+1,max,isRandom);
    }
}

// QuickSort optimizado para obtener complejidad temporal de O(nlogn) como peor caso
void insertionSort(int arr[], int min, int max) {
    for(int i = min + 1; i < max; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int & median3(int arr[],int min, int max) {
    int medio = (max+min)/2;
    if(arr[medio] < arr[min]) {
        swap(arr[min],arr[medio]);
    }else if (arr[max] < arr[min]) {
        swap(arr[min],arr[max]);
    } else if(arr[max] < arr[medio]) {
        swap(arr[medio],arr[max]);
    }
    
    swap(arr[medio],arr[max-1]);
    return arr[max - 1];
}

void quicksortOptimize(int arr[], int min, int max) {
    if(min + 10 <= max) {
        int & pivote = median3(arr, min, max);

        // Particion
        int i = min, j = max - 1;
        for(;;) {
            while (arr[++i] < pivote){}
            while (pivote < arr[--j]){}
            if(i < j)
                swap(arr[i],arr[j]);
            else
                break;
        }

        swap(arr[i],arr[i-1]);

        quicksortOptimize(arr,min,i-1);
        quicksortOptimize(arr,i+1,max);
    }
    else
        insertionSort(arr,min,max);
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
    const int SIZE_LOGARITHMIC = 250000;
    const int TEST_COUNT = 10;
    int arrSize = SIZE_CUADRATIC;
    int timeDuration[TEST_COUNT];
    
    cout << "------------------ Quicksort cuadratico ------------------" << endl;

    for(int j = 0; j < TEST_COUNT; j++) {
        int *arr = new int[arrSize];
        for(int i = 0; i < arrSize; i++) {
            arr[i] = arrSize-1;
        }
        clock_t t = clock();
        quicksort(arr,0,arrSize-1,false);
        t = clock() - t;
        timeDuration[j] = t;
        cout << "Para " << arrSize << " elementos: " << t << " ticks" << endl;
        delete [] arr;
        arrSize += SIZE_CUADRATIC;
    }
    cout << endl << "los resultados anteriores pueden compararse con la funcion: ";
    cout << "f(x) = " << timeDuration[0] << "x^2 -> la cual es cuadratica" << endl;
    cout << "Tasas de Crecimiento:" << endl;
    for(int i = 0; i < TEST_COUNT - 1; i++) {
        cout << "T" << i+1 << " " << timeDuration[i+1] - timeDuration[i];
        cout << "   F" << i+1 << " " << timeDuration[0]*pow(i+2,2) - timeDuration[0]*pow(i+1,2) << endl;
    }

    cout << endl;
    cout << "En este caso, el quicksort() presenta un comportamiento O(n^2), en el cual, se esta \n\
ordenando un arreglo que esta en el orden inverso tomando como pivote el elemento de mas a la derecha. \n\
Se puede apreciar como el algoritmo tiene una tasa de crecimiento muy parecida a la de una funcion \n\
cuadratica, tomando en consideracion que el sistema operativo y los procesos que corren de fondo, \n\
pueden causar muchas variaciones, se puede concluir que dicho algoritmo bajo estas circunstancias \n\
es de una complejidad cuadratica O(n^2)" << endl << endl;

    cout << "------------------ Quicksort logaritmico ------------------" << endl;

    arrSize = SIZE_LOGARITHMIC;
        
    for(int j = 0; j < TEST_COUNT; j++) {
        timeDuration[j] = 0;
    }
    for(int j = 0; j < TEST_COUNT; j++) {
        clock_t t;
        for(int k = 0; k < 20; k++) {
            srand(126);
            int *arr = new int[arrSize];
            for(int i = 0; i < arrSize; i++) {
                arr[i] = arrSize;
            }
            //printArray(arr,arrSize);
            t = clock();
            quicksortOptimize(arr,0,arrSize-1);
            t = clock() - t;
            timeDuration[j] += t;
            
            delete [] arr;
        }
        timeDuration[j] /= 20;
        cout << "Para " << arrSize << " elementos: " << timeDuration[j] << " ticks" << endl;
        arrSize += SIZE_LOGARITHMIC;
    }
    cout << endl << "los resultados anteriores pueden compararse con la funcion: ";
    cout << "f(x) = xlog2(x) + " << timeDuration[0] << "x -> la cual es lineal" << endl;
    cout << "Tasas de Crecimiento:" << endl;
    for(int i = 0; i < TEST_COUNT - 1; i++) {
        cout << "T" << i+1 << " " << timeDuration[i+1] - timeDuration[i];
        double f = ((i+2)*log2(i+2)+timeDuration[0]*(i+2)) - ((i+1)*log2(i+1)+timeDuration[0]*(i+1));
        cout << "   F" << i+1 << " " << f << endl;
    }

    cout << endl;
    cout << "En este caso, el quicksortOptimize() presenta un comportamiento O(nlogn), en el cual, se esta \n\
ordenando un arreglo que esta en el orden inverso. Este quicksort esta optimizado para obtener complejidad temporal\n\
O(nlogn) en el peor de los casos, este algoritmo se obtuvo del libro \"Data Structures and Algorithm analysis in C++\"\n\
Cuarta edicion por Mark Allen Weiss, y este funciona de manera que se elije un pivote medio con un algoritmo de aproximacion\n\
que compara el primer elemento, el elemento del medio y el ultimo elemento para obtener una aproximacion de cual\n\
es el numero medio para usarlo como pivote, de esta forma se optimiza para obtener el mejor caso y caso promedio de forma\n\
frecuente, ademas de usar otro tipo de algoritmo para sorting, para ordenar aquellos subarreglos que sean tan pequennios\n\
que no valga la pena seguir dividiendo en subarrays. De esta forma se obtiene una complejidad temporal O(nlogn) para el peor\n\
de los casos, segun el experimento programado, se puede apreciar que comparando con una funcion del estilo O(nlogn), se puede\n\
obtener resultados muy parecidos en su tasa de crecimiento, ignorando la variabilidad del experimento por procesos de segundo plano\n\
y el sistema operativo. En conclusion, el quicksort puede llegar a ser un algoritmo de O(nlogn)\n\
" << endl << endl;
    
    cout << "------------------ Influencia del pivote ------------------" << endl;
    arrSize = SIZE_CUADRATIC;
    for(int j = 0; j < TEST_COUNT; j++) {
        int *arr = new int[arrSize];
        for(int i = 0; i < arrSize; i++) {
            arr[i] = arrSize-1;
        }
        clock_t t = clock();
        quicksort(arr,0,arrSize-1,true);
        t = clock() - t;
        timeDuration[j] = t;
        cout << "Para " << arrSize << " elementos: " << t << " ticks" << endl;
        delete [] arr;
        arrSize += SIZE_CUADRATIC;
    }
    cout << "Tasas de Crecimiento:" << endl;
    for(int i = 0; i < TEST_COUNT - 1; i++) {
        cout << "T" << i+1 << " " << timeDuration[i+1] - timeDuration[i] << endl;
    }

    cout << endl;
    cout << "En este caso se ve que no hay mucha diferencia con respecto a el pivote fijo primero, cuando\n\
se ordena un arreglo en el orden inverso, pero que pasa si usamos elementos distintos?" << endl << endl;

    arrSize = SIZE_LOGARITHMIC;
    
    int timeDurationFijo[TEST_COUNT];
    for(int j = 0; j < TEST_COUNT; j++) {
        int *arr = new int[arrSize];
        int *arr2 = new int[arrSize];
        srand(126);
        for(int i = 0; i < arrSize; i++) {
            arr[i] = rand();
            arr2[i] = arr[i];
        }

        clock_t t = clock();
        quicksort(arr,0,arrSize-1,true);
        t = clock() - t;
        timeDuration[j] = t;

        t = clock();
        quicksort(arr2,0,arrSize-1,false);
        t = clock() - t;
        timeDurationFijo[j] = t;

        cout << "Para " << arrSize << " elementos: " << timeDuration[j] << " ticks random y " << timeDurationFijo[j] << " ticks para fijo" << endl;
        delete [] arr;
        arrSize += SIZE_CUADRATIC;
    }
    cout << "Tasas de Crecimiento:" << endl;
    for(int i = 0; i < TEST_COUNT - 1; i++) {
        cout << "Random" << i+1 << " " << timeDuration[i+1] - timeDuration[i];
        cout << "   Fijo" << i+1 << " " << timeDurationFijo[i+1] - timeDurationFijo[i] << endl;
    }

    cout << endl;

     cout << "Realmente no existen muchas diferencia entre un pivote fijo y uno random, quitando el hecho que\n\
la funcion random es muy costosa y se ejecuto para el pivote fijo para que esto no influyera en el test, un pivote\n\
se puede decir que un pivote random es tan malo como un pivote fijo, puesto a que es impredecible y puede elegir un mal\n\
pivote o un buen pivote. Para esta prueba se hizo usando elementos random con una seed fija para cada iteracion obtener\n\
los mismos primeros numeros y un par nuevos para poder hacer la comparacion. En conclusion, un pivote fijo y uno random\n\
tienen los mismos problemas, y lo mejor es usar el quicksort optimizado con median of 3 y un sort extra para divisiones\n\
tan pequennias que no tengan sentido seguir dividiendo\n\
"<< endl << endl;


    return 0;
}




