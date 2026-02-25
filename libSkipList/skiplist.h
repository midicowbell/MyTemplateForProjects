#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstdlib>
template<typename Tkey, typename Tvalue>
struct Node
{
	std::pair<Tkey, Tvalue> data;
	Node* next_elem;
	Node* next_lvl;

	Node(const Tkey& key, const Tvalue& value) : data(key, value), next_elem(nullptr), next_lvl(nullptr) { }
};

template<typename Tkey, typename Tvalue>
class SkipList {
private:
	int maxLvl;
	int currLvl;
	Node <Tkey, Tvalue>* head;
public:
	SkipList(int maxlevel) :currLvl = 1, maxlvl(maxlevel) {
		head = new Node<Tkey, Tvalue>(Tkey{}, Tvalue{})
	}
	~SkipList() {
		Node<Tkey, Tvalue>* lvl = head;
		while (lvl) {
			Node<Tkey, Tvalue>* curr = lvl;
			lvl = lvl->next_lvl;
			while (curr) {
				Node<Tkey, Tvalue>* next = curr->next_elem;
				delete curr;
				curr = next;
			}
		}
	}
	int randomLvl() {
		int lvl = 1;
		while ((rand() % 2) && lvl < maxLvl) {
			lvl++;
		}
		return lvl;
	}
	Node<Tkey, Tvalue>* find(const Tkey& key) {
		current = maxLvl;

	}

};