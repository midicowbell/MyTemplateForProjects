#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../libAVLtree/avltree.h"
template<typename Tkey, typename Tvalue>
class TableAVL : public Itable<Tkey, Tvalue> {
private:
	AVLTree<Tkey, Tvalue> _data;
public:
	TableAVL() {}
	~TableAVL() override{}
	bool consist(const Tkey& key) const noexcept override {
		return _data.find(key) != nullptr;
	}
	void insert(const Tkey& key, const Tvalue& value) override {
		_data.insert(key, value);
	}
	void replace(const Tkey& key, const Tvalue& value) override {
		Tvalue* found = _data.find(key);
		if (found != nullptr) {
			*found = value;
		}
		else {
			throw std::invalid_argument("Key not found for replacement");
		}
	}
	Tvalue& find(const Tkey& key) override {
        Tvalue* found = _data.find(key);
        if (found != nullptr) {
            return *found;
        }
        throw std::invalid_argument("Key not found in TableAVL");
    }
	bool is_empty() const noexcept override {
		return _data.is_empty();
	}
	void erase(const Tkey& key) override {
		_data.remove(key);
	}
	std::ostream& print(std::ostream& os) const noexcept override {
		_data.print(os);
		return os;
	}
};