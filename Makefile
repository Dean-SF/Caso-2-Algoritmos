quickCompile:
	g++ -static -Wl,--stack,33554432 -std=c++17 quicksort.cpp -o quicksort && .\quicksort.exe
insertionCompile:
	g++ -static -std=c++17 insertionsort.cpp -o insertionsort && .\insertionsort.exe
freeCompile:
	g++ -static -std=c++17 freetextSearch.cpp -o freetextSearch && .\freetextSearch.exe