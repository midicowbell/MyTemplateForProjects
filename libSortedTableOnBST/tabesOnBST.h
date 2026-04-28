#pragma once
#include "../libBSTree/bstree.h"
#include "../libITable/itable.h"

template<typename Tkey, typename Tvalue>
class TableBST : public Itable<Tkey, Tvalue> {
private:
	BSTree<Tkey, Tvalue> _data;
public:
	TableBST() = default;
	~TableBST() override = default;
	void insert(const Tkey& key, const Tvalue& value) override {
		_data.insert(key, value);
	}
	void erase(const Tkey& key) override {
		_data.remove(key);
	}
	Tvalue& find(const Tkey& key) override {
		Tvalue* ptr = _data.find(key);
		if (ptr == nullptr) {
			throw std::out_of_range("key not found");
		}
		return *ptr;
	}
	bool is_empty() const noexcept override {
		return _data.is_empty();
	}

	bool consist(const Tkey& key) const noexcept override {
		return _data.find(key) != nullptr;
	}
	void replace(const Tkey& key, const Tvalue& value) override {
		Tvalue* ptr = _data.find(key);
		if (ptr != nullptr) {
			*ptr = value;
		}
		else {
			throw std::out_of_range("Key not found for replace");
		}
	}
	void print_ordered(std::ostream& os) const noexcept {
		print_rec(os, _root);
	}

	std::ostream& print(std::ostream& os) const noexcept override {
		_data.print_ordered(os); 
		return os;
	}
};