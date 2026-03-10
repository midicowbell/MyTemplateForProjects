#pragma once
#include <iostream>
#include <queue>

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
private:
	Node<Tkey, Tvalue>* _root;

	void lcr_rec(Node<Tkey, Tvalue>* node) const {
		if (node == nullptr) return;
		lcr_rec(node->left);
		std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
		lcr_rec(node->right);
	}
	void lrc_rec(Node<Tkey, Tvalue>* node) const {
		if (node == nullptr) return;
		lrc_rec(node->left);
		lrc_rec(node->right);
		std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
	}

	void clr_rec(Node<Tkey, Tvalue>* node) const {
		if (node == nullptr) return;
		std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
		clr_rec(node->left);
		clr_rec(node->right);
	}
	void width_rec() const {
		if (is_empty()) {
			std::cout << "Width: Tree is empty" << std::endl;
			return;
		}

		std::queue<Node<Tkey, Tvalue>*> q;
		q.push(_root);
		int level = 0;

		while (!q.empty()) {
			int levelSize = q.size();
			std::cout << "Level " << level << ": ";

			for (int i = 0; i < levelSize; i++) {
				Node<Tkey, Tvalue>* node = q.front();
				q.pop();

				std::cout << "(" << node->data.first << ":" << node->data.second << ") ";

				if (node->left != nullptr) {
					q.push(node->left);
				}
				if (node->right != nullptr) {
					q.push(node->right);
				}
			}

			std::cout << std::endl;
			level++;
		}
	}

	void deleteTree(Node<Tkey, Tvalue>* node) {
		if (node == nullptr) return;
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}

public:
	Tree() {
		_root = nullptr;
	}

	~Tree() {
		deleteTree(_root);
	}
	void insert(const Tkey& key, const Tvalue& value) {
		if (_root == nullptr) {
			_root = new Node<Tkey, Tvalue>(key, value);
			return;
		}

		std::queue<Node<Tkey, Tvalue>*> q;
		q.push(_root);

		while (!q.empty()) {
			Node<Tkey, Tvalue>* node = q.front();
			q.pop();

			if (key < node->data.first) {
				if (node->left == nullptr) {
					node->left = new Node<Tkey, Tvalue>(key, value);
					return;
				}
				else {
					q.push(node->left);
				}
			}
			else if (key > node->data.first) {
				if (node->right == nullptr) {
					node->right = new Node<Tkey, Tvalue>(key, value);
					return;
				}
				else {
					q.push(node->right);
				}
			}
			else {
				node->data.second = value;
				return;
			}
		}
	}

	bool is_empty() const {
		return _root == nullptr;
	}
	void lcr() const {
		std::cout << "LCR (Левое → Корень → Правое): ";
		lcr_rec(_root);
		std::cout << std::endl;
	}

	void lrc() const {
		std::cout << "LRC (Левое → Правое → Корень): ";
		lrc_rec(_root);
		std::cout << std::endl;
	}

	void clr() const {
		std::cout << "CLR (Корень → Левое → Правое): ";
		clr_rec(_root);
		std::cout << std::endl;
	}

	void width() const {
		std::cout << "WIDTH (В ШИРИНУ):" << std::endl;
		width_rec();
	}
};