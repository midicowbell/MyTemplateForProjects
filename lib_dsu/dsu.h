#pragma once
class DSU {
	int* _parent;
	size_t _size;
	int* _rank;
public:
	size_t size() { return _size; }
	DSU(size_t size);
	~DSU();
	void unite(int x1, int x2);
	int find(int x);
};
