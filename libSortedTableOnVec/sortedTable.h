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

	// Вспомогательный метод для проверки существования элемента по позиции
	// Возвращает true если элемент с заданным ключом находится в позиции
	bool _isKeyAtPosition(size_t pos, const Tkey& key) const noexcept {
		return pos < _rows.size() && _rows[pos].first == key;
	}

public:
	SortedTableOnVec() = default;
	virtual ~SortedTableOnVec() = default;

	size_t binary_search(const Tkey& key) const {
		size_t left = 0;
		size_t right = _rows.size();
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (_rows[mid].first == key) {
				return mid;
			}
			else if (_rows[mid].first < key) {
				left = mid + 1;
			}
			else {
				right = mid;
			}
		}
		return left;
	}

	void insert(const Tkey& key, const Tvalue& value) override {
		size_t pos = binary_search(key);
		if (_isKeyAtPosition(pos, key)) {
			throw std::logic_error("Key already exists");
		}
		_rows.insert(pos, { key, value });
	}

	void replace(const Tkey& key, const Tvalue& value) override {
		size_t pos = binary_search(key);
		if (_isKeyAtPosition(pos, key)) {
			_rows[pos].second = value;
		}
		else {
			_rows.insert(pos, { key, value });
		}
	}

	bool consist(const Tkey& key) const noexcept override {
		size_t pos = binary_search(key);
		return _isKeyAtPosition(pos, key);
	}

	Tvalue& find(const Tkey& key) override {
		size_t pos = binary_search(key);
		if (_isKeyAtPosition(pos, key)) {
			return _rows[pos].second;
		}
		throw std::out_of_range("Key not found");
	}

	void erase(const Tkey& key) override {
		size_t pos = binary_search(key);
		if (_isKeyAtPosition(pos, key)) {
			_rows.erase(pos, 1);
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