#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../libTvector/tvector.h"
#include "../libITable/itable.h"
#include <string.h>
#define SIZE 100
#define SHIFT 7
template<typename Tvalue>
struct HashDate
{
	enum States { EMPTY, BUSY,DELETED };
	States _state = EMPTY;
	std::string _key;
	Tvalue _data;
};
template<typename Tvalue>
class HashTableOA{  // : public Itable<std::string, Tvalue> доделать
private:
	Tvector<HashDate<Tvalue>> _rows;
	size_t _size;
	size_t _count = 0;
	size_t _shift = 1;
	size_t h(const std::string& key) {
		size_t hash = 0;
		for (int i = 0; i < key.length(); i++) {
			hash += key[i];
		}
		hash %= _size;
		return hash;
	}
	size_t hh(size_t hash) {
		return (hash + _shift) % _size;
	}
	bool is_simple(size_t a, size_t b) {
		while (b) {
			a %= b;
			std::swap(a, b);
		}
		return a == 1;
	}
	bool is_full() {
		return _count >= _size;
	}

public:
	HashTableOA() : _size(SIZE), _shift(SHIFT) {}
	HashTableOA(size_t s) : _size(s) {
		_rows.resize(_size);

		for (size_t i = std::max(static_cast<size_t>(2), _size / 15); i < _size; i++) {
			if (is_simple(i, _size)) {_shift = i;}
		}
	}


	void insert(const std::string& key, const Tvalue& value) {
		if (is_full()) {
			return;
		}
		size_t hash = h(key);
		while (1) {
			if (_rows[hash]._state != HashDate<Tvalue>::BUSY) {
				_rows[hash]._state = HashDate<Tvalue>::BUSY;
				_rows[hash]._data = value;
				_rows[hash]._key = key;
				return;
			}
			if (_rows[hash]._key == key) {
				throw std::logic_error("Key already exist");
				return;
			}
			hash = hh(hash);
		}
	}
	void erase(const std::string& key) {
		size_t hash = h(key);
		first_hash = hash;
		while (1) {
			if (_rows[hash]._state == EMPTY) {
				break;
			}
			if (_rows[hash]._state == BUSY && _rows[hash]._key == key) {
				_rows[hash]._state = DELETED;
				return;
			}
			hash = hh(hash);
			if (first_hash == hash) { break; }
		}
		throw std::logic_error("key not found");

	}

	Tvalue* find(const std::string& key) {
		size_t hash = h(key);
		while (1) {
			if (_rows[hash]._state == HashDate<Tvalue>::EMPTY) {
				return nullptr;
			}
			if (_rows[hash]._state == HashDate<Tvalue>::BUSY && _rows[hash]._key == key) {
				return &_rows[hash]._data;
			}
			hash = hh(hash);
		}
	}

	void print() {
		for (int i = 0; i < _size; i++) {
			if (_rows[i]._state == HashDate<Tvalue>::BUSY) {
				std::cout << _rows[i]._key << " " << _rows[i]._data << "\n";
			}
				
		}
	}

};