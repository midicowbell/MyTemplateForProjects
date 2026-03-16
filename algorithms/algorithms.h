#pragma once
template<typename Tkey, typename Tvalue>
void sortMass(Tkey* arr, int size) {
	Tree<Tkey, Tvalue> mass;
	for (int i = 0; i < size; i++) {
		mass.insert(arr[i], Tvalue());
	}
	std::cout << "sorted mass:\n";
	mass.lcr();
}