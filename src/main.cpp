#include "../libSkipList/skiplist.h"


int main() {
	SkipList<int, std::string> sl(4);

	// Вставляем элементы
	sl.insert(3, "three");
	sl.insert(6, "six");
	sl.insert(7, "seven");
	sl.insert(9, "nine");
	sl.insert(12, "twelve");
	sl.insert(17, "seventeen");
	sl.insert(19, "nineteen");
	sl.insert(21, "twenty-one");

	std::cout << "=== Skip List ===" << std::endl;
	sl.print();

	// Поиск элементов
	std::cout << "=== Search ===" << std::endl;
	auto found = sl.find(7);
	if (found) {
		std::cout << "Found: " << found->_data.first << " -> " << found->_data.second << std::endl;
	}

	found = sl.find(100);
	if (!found) {
		std::cout << "100 not found" << std::endl;
	}

	// Обновление значения
	sl.insert(7, "SEVEN!");
	std::cout << "\n=== After update ===" << std::endl;
	sl.print();

	// Удаление
	sl.remove(7);
	std::cout << "=== After removing 7 ===" << std::endl;
	sl.print();

	return 0;
}