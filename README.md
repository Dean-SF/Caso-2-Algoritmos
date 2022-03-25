# Caso 2 Algoritmos

Compilado con MinGW de 64 bits en windows.  
Hecho por Deyan Sanabria Fallas #2021046131.  
Todo caso esta documentado en la ejecucion del main() puesto que fue hecho para que los experimentos funcionen independientemente del computador,
ejecutar con la menor cantidad de procesos activos para unos resultados mas acertados

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
  
#### Caso O(nlogn):
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
  
Para este caso, se puede apreciar que las tasas de crecimiento son levemente parecidas, estas van en un aumento muy leve
pero para los tiempos de nuestro experimento son bastante perjudicados por los procesos de fondo y el sistema operativo,
esto hace que a veces varie demasiado la tasa de crecimiento, pero se nota una tendencia a crecer en ciertas partes
lo que es comparable a la ecuacion presentada en los experimentos. Por ello, concluyo que para este caso, el algoritmo
quicksort tiene un comportamiento de O(nlogn)

#### Caso Cuadratico:
Para este caso es bastante simple, se usa el quicksort sin optimizar, este tiene un pivote fijo el cual es el ultimo
elemento del subarreglo, en este caso, el cual es ordenar un arreglo que esta en el orden inverso, causa que el pivote 
quede en un extremo, el cual es el minimo para la primera iteracion, y todos los elementos del subarray restantes son mayores a el
haciendo que las divisiones del arreglo, sean muy desbalanceadas, causando un comportamiento cuadratico, como lo muestra el siguiente
experimento:
  
>------------------ Quicksort cuadratico ------------------  
>Para 5000 elementos: 14 ticks  
>Para 10000 elementos: 53 ticks  
>Para 15000 elementos: 121 ticks  
>Para 20000 elementos: 220 ticks  
>Para 25000 elementos: 340 ticks  
>Para 30000 elementos: 471 ticks  
>Para 35000 elementos: 639 ticks  
>Para 40000 elementos: 835 ticks  
>Para 45000 elementos: 1077 ticks  
>Para 50000 elementos: 1304 ticks  
>  
>los resultados anteriores pueden compararse con la funcion: f(x) = 14x^2 -> la cual es cuadratica  
>Tasas de Crecimiento:  
>T1 39   F1 42  
>T2 68   F2 70  
>T3 99   F3 98  
>T4 120   F4 126  
>T5 131   F5 154  
>T6 168   F6 182  
>T7 196   F7 210  
>T8 242   F8 238  
>T9 227   F9 266  
  
Se puede apreciar que la tasa de crecimiento llega a tener cierto parecido con la de la funcion cuadratica sugerida
teniendo en cuenta procesos de fondo y el sistema operativo, creo que es bastante evidente que la tasa de crecimiento
se parece mucho a la de una funcion cuadratica, por lo tanto concluyo que el quicksort para esta caso es O(n^2) cuadratico

#### Influencia del pivote:
De los experimentos anteriores se puede ver que el pivote influye bastante a la hora de hacer las divisiones del arreglo,
sin embargo, ¿como se compara un pivote fijo con uno random? para ello el siguiente experimento:
  
>------------------ Influencia del pivote ------------------  
>Para 5000 elementos: 14 ticks  
>Para 10000 elementos: 52 ticks  
>Para 15000 elementos: 118 ticks  
>Para 20000 elementos: 209 ticks  
>Para 25000 elementos: 327 ticks  
>Para 30000 elementos: 472 ticks  
>Para 35000 elementos: 641 ticks  
>Para 40000 elementos: 842 ticks  
>Para 45000 elementos: 1066 ticks  
>Para 50000 elementos: 1306 ticks  
>Tasas de Crecimiento:  
>T1 38  
>T2 66  
>T3 91  
>T4 118  
>T5 145  
>T6 169  
>T7 201  
>T8 224  
>T9 240  
  
En este caso se aplico el mismo experimento que para el caso anterior cuadraticoy se puede ver que el experimento salio parecido, tanto en
tasas de crecimiento como en tiempos, asi que se aplico otro experimento:
  
>Para 250000 elementos: 42 ticks random y 39 ticks para fijo  
>Para 500000 elementos: 83 ticks random y 82 ticks para fijo  
>Para 750000 elementos: 132 ticks random y 129 ticks para fijo  
>Para 1000000 elementos: 183 ticks random y 181 ticks para fijo  
>Para 1250000 elementos: 232 ticks random y 230 ticks para fijo  
>Para 1500000 elementos: 287 ticks random y 274 ticks para fijo  
>Para 1750000 elementos: 341 ticks random y 328 ticks para fijo  
>Para 2000000 elementos: 392 ticks random y 393 ticks para fijo  
>Para 2250000 elementos: 453 ticks random y 443 ticks para fijo  
>Para 2500000 elementos: 501 ticks random y 508 ticks para fijo  
>Tasas de Crecimiento:  
>Random1 41   Fijo1 43  
>Random2 49   Fijo2 47  
>Random3 51   Fijo3 52  
>Random4 49   Fijo4 49  
>Random5 55   Fijo5 44  
>Random6 54   Fijo6 54  
>Random7 51   Fijo7 65  
>Random8 61   Fijo8 50  
>Random9 48   Fijo9 65  
  
Este experimento fue usando dos arreglos iguales, ambos contenian numeros random pero de una semilla en especifico que se volvia a
iniciar cada iteracion, haciendo que los primeros elementos sean iguales y solo cambien los nuevos numeros que ingresan. 
Para este experimento se puede apreciar que no hay demasiadas variaciones para concluir una ventaja de uno por encima del otro
puesto a que tanto las tasas de crecimiento como los tiempos son parecidos teniendo en cuenta las variaciones del sistema operativo
y los procesos de fondo, por ende concluyo que el pivote random y el fijo son igual de malos, puesto a que ambos tienen la probabilidad
de ser muy buen pivote o muy mal pivote dependiendo de como este ordenado el arreglo y la aleatoriedad e impredecibilidad del pivote random.

## Free Text Search
Para finalizar, el algoritmo que desarrolle para hacer busquedas de palabras dentro de un texto, para este algoritmo se utilizo un Trie Tree donde
se almacenan palabras que esten dentro de un texto, en el main se puede encontrar dos variables constantes, una llamada `FILENAME` y otra llamada
`WORDTOFIND`, la primer variable se le coloca el nombre del archivo que se va a analizar, para ello, el archivo se debe encontrar en la carpeta 'textos'
donde ya hay un texto de prueba, pero se pueden colocar mas, la segunda variable es la palabra a buscar. Ambas se pueden modificar para probar el algoritmo.
  
Al hacer uso de un Trie Tree, las busquedas son increiblemente rapidas y lo que mas tarda de dicho algoritmo es la carga del archivo, mientras
se carga el archivo se guardan las palabras en el trie, cualquier letra mayuscula pasa a minuscula por facilidad y solo se incluyen palabras con
letras del abecedario anglosajon, nada de numeros ni simbolos.

# COMO USAR / COMO COMPILAR
Dentro del repositorio se encuentra un makefile con el que se puede compilar todos los programas. Para compilar cada uno se hace de la siguiente forma:
  
#### Quick Sort:
>make quick  
#### Insertion Sort:
>make insertion  
#### Free Text Search:
>make free  
  
todos los comandos se ejecutan estando en la carpeta del repositorio
