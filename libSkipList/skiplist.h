#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstdlib>
#include <vector>

template<typename Tkey, typename Tvalue>
struct Node
{
	std::pair<Tkey, Tvalue> _data;
	std::vector<Node*> forward;

	Node(const Tkey& key, const Tvalue& value, int level)
		: _data(key, value), forward(level, nullptr) {
	}
};

template<typename Tkey, typename Tvalue>
class SkipList {
private:
	int maxLvl;
	int currLvl;
	Node<Tkey, Tvalue>* head;

public:
	SkipList(int maxlvl) : currLvl(1), maxLvl(maxlvl) {
		head = new Node<Tkey, Tvalue>(Tkey{}, Tvalue{}, maxLvl);
	}
	~SkipList() {
		Node<Tkey, Tvalue>* curr = head->forward[0];
		while (curr) {
			Node<Tkey, Tvalue>* next = curr->forward[0];
			delete curr;
			curr = next;
		}
		delete head;
	}
	int randomLvl() {
		int lvl = 1;
		while ((rand() % 3 != 0) && lvl < maxLvl) {
			lvl++;
		}
		return lvl;
	}
	Node<Tkey, Tvalue>* find(const Tkey& key) noexcept {
		Node<Tkey, Tvalue>* curr = head;
		for (int lvl = currLvl - 1; lvl >= 0; lvl--) {
			while (curr->forward[lvl] && curr->forward[lvl]->_data.first < key) {
				curr = curr->forward[lvl];
			}
		}
		curr = curr->forward[0];
		if (curr && curr->_data.first == key) {
			return curr;
		}
		return nullptr;
	}
	void insert(const Tkey& key, const Tvalue& value) {
		Node<Tkey, Tvalue>* curr = head;
		std::vector<Node<Tkey, Tvalue>*> update(maxLvl, nullptr);
		for (int lvl = currLvl - 1; lvl >= 0; lvl--) {
			while (curr->forward[lvl] && curr->forward[lvl]->_data.first < key) {
				curr = curr->forward[lvl];
			}
			update[lvl] = curr;
		}
		curr = curr->forward[0];
		if (curr && curr->_data.first == key) {
			curr->_data.second = value;
			return;
		}
		int newLvl = randomLvl();
		if (newLvl > currLvl) {
			for (int lvl = currLvl; lvl < newLvl; lvl++) {
				update[lvl] = head;
			}
			currLvl = newLvl;
		}
		Node<Tkey, Tvalue>* newNode = new Node<Tkey, Tvalue>(key, value, newLvl);
		for (int lvl = 0; lvl < newLvl; lvl++) {
			newNode->forward[lvl] = update[lvl]->forward[lvl];
			update[lvl]->forward[lvl] = newNode;
		}
	}
	bool remove(const Tkey& key) {
		Node<Tkey, Tvalue>* curr = head;
		std::vector<Node<Tkey, Tvalue>*> update(maxLvl, nullptr);
		for (int lvl = currLvl - 1; lvl >= 0; lvl--) {
			while (curr->forward[lvl] && curr->forward[lvl]->_data.first < key) {
				curr = curr->forward[lvl];
			}
			update[lvl] = curr;
		}
		curr = curr->forward[0];
		if (!curr || curr->_data.first != key) {
			return false;
		}
		for (int lvl = 0; lvl < currLvl; lvl++) {
			if (update[lvl]->forward[lvl] != curr) {
				break;
			}
			update[lvl]->forward[lvl] = curr->forward[lvl];
		}
		while (currLvl > 1 && !head->forward[currLvl - 1]) {
			currLvl--;
		}
		delete curr;
		return true;
	}
	void print() const {
		for (int lvl = currLvl - 1; lvl >= 0; lvl--) {
			std::cout << "level " << lvl << ": ";
			Node<Tkey, Tvalue>* curr = head->forward[lvl];
			while (curr) {
				std::cout << "(" << curr->_data.first << ":" << curr->_data.second << ") ";
				curr = curr->forward[lvl];
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
};