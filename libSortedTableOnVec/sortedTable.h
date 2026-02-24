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
	size_t binary_search(const Tkey& key) {
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
		if (consist(key)) { throw std::logic_error("Key already exists"); }
		size_t pos =  binary_search(key);
		_rows.insert(static_cast<int>(pos), { key, value });

	}
	void replace(const Tkey& key, const Tvalue& value) override {
		for (size_t i = 0; i < _rows.size(); i++) {
			if (_rows[i].first == key) {
				_rows[i].second = value;
				return;
			}
		}
		insert(key, value);

	}
	bool consist(const Tkey& key) const noexcept override {
		size_t left = 0;
		size_t right = _rows.size();
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (_rows[mid].first == key) { return true; }
			else if (_rows[mid].first < key) { left = mid + 1; }
			else { right = mid; }
		}
		return false;
	}
	Tvalue& find(const Tkey& key) const override {
		size_t left = 0;
		size_t right = _rows.size();
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (_rows[mid].first == key) { return const_cast<Tvalue&>(_rows[mid].second); }
			else if (_rows[mid].first < key) { left = mid + 1; }
			else { right = mid; }

		}
		throw std::out_of_range("Key not found");
	}
	void erase(const Tkey& key) override {
		for (size_t i = 0; i < _rows.size(); i++) {
			if (_rows[i].first == key) {
				_rows.erase(i, 1);
				return;
			}
		}
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