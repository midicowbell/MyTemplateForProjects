#pragma once
#include <iostream>
template<typename Tkey, typename Tvalue>
struct Node {
	std::pair<Tkey, Tvalue> data;
	Node* left;
	Node* right;

public:
	Node(const Tkey& key, const Tvalue& value)
		: data(key, value), left(nullptr), right(nullptr) {
	}

	Node() : data(), left(nullptr), right(nullptr) {}
};

template<typename Tkey, typename Tvalue>
class Tree {
	Node* _root;
public:
	Tree() {
		_root = nullptr;
	}
	~Tree() {
		delete _root;
	}
	void insert(const Tkey& key, const Tvalue& value) {
		Node* node = new Node(key, value);
		if (is_empty()) { _root = node; return; }
		
	}
	bool is_empty() {
		return _root == nullptr;
	}
};