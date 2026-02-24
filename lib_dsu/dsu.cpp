#include "dsu.h"
DSU::DSU(size_t size) : _size(size) {
	_parent = new int[_size];
	_rank = new int[_size];
	for (int i = 0; i < _size; i++) {
		_parent[i] = i;
		_rank[i] = 0;
	}
}
DSU::~DSU() {
	delete[] _parent;
	delete[] _rank;
}
void DSU::unite(int x1, int x2) {
	int x_1 = _rank[find(x1)];
	int x_2 = _rank[find(x2)];
	if (x_1 < x_2) {
		_parent[find(x1)] = find(x2);
	}
	else {
		if (x_1 == x_2) {
			_rank[find(x1)]++;
		}
		_parent[find(x2)] = find(x1);
	}
}
int DSU::find(int x) {
	if (_parent[x] == x) {
		return x;
	}
	else {

		return _parent[x] = find(_parent[x]);
	}
}
