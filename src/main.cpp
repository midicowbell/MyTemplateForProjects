#include <sstream>
#include <windows.h>
#include "Tree.h"
#include "../algorithms/algorithms.h"
void main() {
	SetConsoleCP(65001);      
	SetConsoleOutputCP(65001);
	int mass[8] = { 1, 5, 4, 2, 23, 213412, 51251424, 4214124 };
	sortMass<int, int>(mass, 8);
	
}