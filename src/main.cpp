#include "../libHashTable/hashTable.h"
#include <vector>

int main() {
	std::vector<std::pair<std::string, int>> dict2 = { {"massive", 4312}, {"list", 5863}, {"hash", 4372}, {"vector", 2588}};
	std::vector<std::pair<std::string, int>> dict1 = { {"table", 1349}, {"hash", 1985}, {"list", 4372} };
	HashTableOA<int>table(20);
	for (const auto& item : dict1) {
		table.insert(item.first, item.second);
	}
	for (const auto& item : dict2) {
		if (table.find(item.first) == nullptr) {
			table.insert(item.first, item.second);
		}
	}

	table.print();
	//int* val1 = table.find("hash");
	//int* val2 = table.find("list");
	//if (val1 && val2) std::cout << "hash: " << *val1 << "\nlist:"  << *val2<< std::endl;
}

