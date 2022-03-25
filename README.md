# Caso 2 Algoritmos

Compilado con MinGW de 64 bits en windows.  
Hecho por Deyan Sanabria Fallas #2021046131

## Insertion Sort
Este sort puede ser lineal o cuadratico. Por la forma del algoritmo, a simple vista se puede obtener de forma
teorica que dicho algoritmo es lineal cuando se ordena un array previamente ordenado, puesto a que solo va a
recorrer el Array "n" veces y esto se puede ver de la siguiente manera:

#### Caso lineal:
>--- --- --- TEST CASO LINEAL --- --- ---  
>Para 2000000 elementos: 6 ticks  
>Para 4000000 elementos: 11 ticks  
>Para 6000000 elementos: 17 ticks  
>Para 8000000 elementos: 21 ticks  
>Para 10000000 elementos: 28 ticks  
>Para 12000000 elementos: 33 ticks  
>Para 14000000 elementos: 38 ticks  
>Para 16000000 elementos: 47 ticks  
>Para 18000000 elementos: 49 ticks  
>Para 20000000 elementos: 52 ticks  
>  
>los resultados anteriores pueden compararse con la funcion: f(x) = 6x -> la cual es cuadratica  
>Tasas de Crecimiento:  
>T1 5   F1 6  
>T2 6   F2 6  
>T3 4   F3 6  
>T4 7   F4 6  
>T5 5   F5 6  
>T6 5   F6 6  
>T7 9   F7 6  
>T8 2   F8 6  
>T9 3   F9 6  
  
Se pueder apreciar que para este caso, la tasa de crecimiento varia entre un -3 y un +3 alrededor de 6,
lo que se puede interpretar como la variabilidad causada por todos los procesos de fondo y el sistema
operativo trabajando al momento de ejecutar el programa, pero la conclusion queda igual, no varia lo suficiente
como para no considerarlo un algoritmo lineal.

#### Caso cuadratico:
Cualquier otro caso del insertion sort va ser cuadratico, y para ello el siguiente experimento:

>--- --- --- TEST CASO CUADRATICO --- --- ---  
>Para 5000 elementos: 22 ticks  
>Para 10000 elementos: 90 ticks  
>Para 15000 elementos: 203 ticks  
>Para 20000 elementos: 358 ticks  
>Para 25000 elementos: 557 ticks  
>Para 30000 elementos: 795 ticks  
>Para 35000 elementos: 1081 ticks  
>Para 40000 elementos: 1414 ticks  
>Para 45000 elementos: 1779 ticks  
>Para 50000 elementos: 2201 ticks  
>  
>los resultados anteriores pueden compararse con la funcion: f(x) = 22x^2 -> la cual es cuadratica  
>Tasas de Crecimiento:  
>T1 68   F1 66  
>T2 113   F2 110  
>T3 155   F3 154  
>T4 199   F4 198  
>T5 238   F5 242  
>T6 286   F6 286  
>T7 333   F7 330  
>T8 365   F8 374  
>T9 422   F9 418  
  
En este caso se esta ordenando un arreglo que esta en el orden inverso y se logra una tasa de crecimiento
cuadratica por la naturaleza del algoritmo

## Quick Sort
El quicksort es un algoritmo particular, tiene como peor caso el ser cuadratico y el mejor caso el ser lineal O(nlogn), al menos
el libro dado por el profesor menciona que O(nlogn) es lineal, no logaritmico. Existe una version del quicksort optimizada para
obtener en el peor de los casos O(nlogn), o al menos obtenerla de forma mas frecuente, y esta fue usada para experimentar con ello,
esta version se encuentra en el libro "Data Structures and Algorithm analysis in C++ Forth Edition" por Mark Allen Weiss, 
donde se usa un pivote que es el numero mas cercano a la mediana del arreglo de numeros, esto se hace con el algoritmo
`Median of 3` que utiliza el numero en la primera posicion, posicion del medio y posicion final del subarreglo para encontrar
el numero medio, ademas que llegados a cierta cantidad de elementos en los subarreglos, se deja de dividir y se ordenan con otro
algoritmo de sorting, en este caso se uso el insertion sort. Asi que para empezar con los casos, primero con el caso O(nlogn)
  
#### Caso O(nlogn)
Para este caso se uso el algoritmo optimizado de quick sort, y se ordeno un arreglo que ya estaba ordenado, se hizo multiples
veces con la misma cantidad de elementos y se obtuvo un promedio para obtener una cantidad mas precisa, y asi queda el experimento:  
>------------------ Quicksort logaritmico ------------------  
>Para 250000 elementos: 14 ticks  
>Para 500000 elementos: 29 ticks  
>Para 750000 elementos: 46 ticks  
>Para 1000000 elementos: 63 ticks  
>Para 1250000 elementos: 79 ticks  
>Para 1500000 elementos: 98 ticks  
>Para 1750000 elementos: 117 ticks  
>Para 2000000 elementos: 134 ticks  
>Para 2250000 elementos: 151 ticks  
>Para 2500000 elementos: 167 ticks  
>  
>los resultados anteriores pueden compararse con la funcion: f(x) = xlog2(x) + 14x -> la cual es lineal  
>Tasas de Crecimiento:  
>T1 15   F1 16  
>T2 17   F2 16.7549  
>T3 17   F3 17.2451  
>T4 16   F4 17.6096  
>T5 19   F5 17.9001  
>T6 19   F6 18.1417  
>T7 17   F7 18.3485  
>T8 17   F8 18.5293  
>T9 16   F9 18.69  


