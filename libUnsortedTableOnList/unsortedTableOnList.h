#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../libITable/itable.h"
#include "list.h"
template<typename Tkey, typename Tvalue>
class UnsortedTableOnList : public Itable<Tkey, Tvalue> {
private:
	List<std::pair<Tkey, Tvalue>> _list;
public:
	UnsortedTableOnList() {}
	~UnsortedTableOnList() {}
	bool consist(const Tkey& key) const noexcept override {
		for (auto it = _list.begin(); it != _list.end(); ++it) {
			if ((*it).first == key) { return true; }
		}
		return false;
	}
	void insert(const Tkey& key, const Tvalue& value) override {
		if(consist(key)) { throw std::logic_error("Key already exists"); }
		_list.push_back({ key ,value });
	}
	void replace(const Tkey& key, const Tvalue& value) override {
		for (auto it = _list.begin(); it != _list.end(); ++it) {
			if ((*it).first == key) {
				(*it).second = value;
				return;
			}
		}
		insert(key, value);
	}
	Tvalue& find(const Tkey& key) const override {
		for (auto it = _list.begin(); it != _list.end(); ++it) {
			if ((*it).first == key) {
				return (*it).second;
			}
		}
		throw std::logic_error("Key not found"); 
	}
	bool is_empty() const noexcept override {
		return _list.is_empty();
	}
	void erase(const Tkey& key) override {
		int pos = 0;
		for (auto it = _list.begin(); it != _list.end(); ++it, ++pos) {
			if ((*it).first == key) {
				_list.erase(pos);
				return;
			}
		}

	}
	std::ostream& print(std::ostream& os) const noexcept override {
		for (auto it = _list.begin(); it != _list.end(); ++it) {
			os << "|" << (*it).first << "|" << (*it).second << "|\n";
		}
		return os;
	}
};