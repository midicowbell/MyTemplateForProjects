#include <sstream>
#include <windows.h>
#include "Tree.h"
#include "../algorithms/algorithms.h"
#include "../libHeap/heap.h"

void main() {
	SetConsoleCP(65001);      
	SetConsoleOutputCP(65001);
	std::srand(time(0));
	std::vector<int> v;
	std::cout << "Неотсортированный массив:\n";
	for (int i = 0; i < 20; i++) {
		v.push_back(rand() % 1000);
		std::cout << " " << v[i];
	}
	std::cout << "\n";
	std::cout << "Отсортированный массив:\n";
	heapSort(v);
	for (int i = 0; i < 20; i++) {
		std::cout << " " << v[i];
	}
	
		
	
}