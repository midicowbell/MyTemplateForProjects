#pragma once
#include <vector>
template<typename Tkey, typename Tvalue>
void sortMass(Tkey* arr, int size) {
	Tree<Tkey, Tvalue> mass;
	for (int i = 0; i < size; i++) {
		mass.insert(arr[i], Tvalue());
	}
	std::cout << "sorted mass:\n";
	mass.lcr();
}

template<typename T>
void heapSort(std::vector<T>& arr) {
    MinHeap<T> heap;
    for (const T& item : arr) {
        heap.add(item);
    }
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = heap.pop();
    }
}