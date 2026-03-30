#include <sstream>
#include <windows.h>
#include "Tree.h"
#include "../algorithms/algorithms.h"
#include "../libHeap/heap.h"
#include "../libQueueOnHeap/queue.h"
template<typename Pr, typename Val>
void printK(const std::vector<std::pair<Pr, Val>> data, int k) {
	QueueOnHeap<Pr, Val> pq;
	for (const auto& item : data) {
		pq.push(item.first, item.second);
	}
	for (int i = 0; i < k && !pq.empty(); i++) {
		auto item = pq.pop();
		std::cout << "\n" <<"Приоритет: " <<item.first << " " << item.second;
	}
}


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

	QueueOnHeap<int, std::string> _queue;
	std::vector < std::pair<int, std::string>> date;
	for (int i = 0; i < 20; i++) {
		std::string val = "data_" + std::to_string(i);
		int priority = rand() % 100;
		date.push_back({ priority, val });
	}
	printK(date, 15);

	//while (true) {
	//	std::cout << "\nприоритет:\n";
	//	int a;
	//	std::cin >> a;
	//	if (a < 0) {
	//		break;
	//	}
	//	std::cout << "\nстрока:\n";
	//	std::string str;
	//	std::cin >> str;
	//	_queue.push(a, str);

	//}
	//while (!_queue.empty()) {
	//	std::cout << "\n" << _queue.pop();
	//}
	
		
	
}