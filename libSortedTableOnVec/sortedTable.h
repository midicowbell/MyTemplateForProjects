#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../libTvector/tvector.h"
#include "../libITable/itable.h"
template<typename Tkey, typename Tvalue>
class SortedTableOnVec : public Itable<Tkey, Tvalue> {
private:
	Tvector<std::pair<Tkey, Tvalue>> _rows;
public:
	SortedTableOnVec() {}
	virtual ~SortedTableOnVec() = default;
	size_t binary_search(const Tkey& key) const {
		size_t left = 0;
		size_t right = _rows.size();
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (_rows[mid].first == key) { return mid; }
			else if (_rows[mid].first < key) {
				left = mid + 1;
			}
			else { right = mid; }
		}
		return left;
	}
	void insert(const Tkey& key, const Tvalue& value) override {
		size_t pos = binary_search(key);
		if (pos < _rows.size() && _rows[pos].first == key)
			throw std::logic_error("Key already exists");
		_rows.insert(pos, { key, value });	
	}

	void replace(const Tkey& key, const Tvalue& value) override {
		size_t pos = binary_search(key);
		if (pos < _rows.size() && _rows[pos].first == key)
			_rows[pos].second = value;
		else
			_rows.insert(static_cast<int>(pos), { key, value });
	}

	bool consist(const Tkey& key) const noexcept override {
		size_t pos = binary_search(key);
		return pos < _rows.size() && _rows[pos].first == key;
	}

	Tvalue& find(const Tkey& key) override {
		size_t pos = binary_search(key);
		if (pos == _rows.size() || _rows[pos].first != key)
			throw std::out_of_range("Key not found");
		return _rows[pos].second;
	}

	void erase(const Tkey& key) override {
		size_t pos = binary_search(key);
		if (pos < _rows.size() && _rows[pos].first == key)
			_rows.erase(pos, 1);
	}
	bool is_empty() const noexcept override {
		return _rows.empty();
	}

	size_t size() const noexcept {
		return _rows.size();
	}
	std::ostream& print(std::ostream& os) const noexcept override {
		for (size_t i = 0; i < _rows.size(); i++) {
			os << "|" << _rows[i].first << " | " << _rows[i].second << "|" << std::endl;
		}
		return os;
	}
};