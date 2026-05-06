#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../libTvector/tvector.h"
#include "../libITable/itable.h"
#include <string.h>
#include <vector>
template<typename Tvalue>
struct HashDate {
    enum States { EMPTY, BUSY, DELETED };
    States _state = EMPTY;
    std::string _key = "";
    Tvalue _data = {};
};

template<typename Tvalue>
class HashTableDoubleHashing : public Itable<std::string, Tvalue> {
private:
    std::vector<HashDate<Tvalue>> _rows;
    size_t _size;
    size_t _count = 0;

    size_t h1(const std::string& key) const {    // начальная позиция
        size_t hash = 0;
        for (char c : key) hash = hash * 31 + static_cast<unsigned char>(c);
        return hash % _size;
    }

    size_t h2(const std::string& key) const {  // шаг, с которым прыгаем по таблице, если занято
        size_t hash = 0;
        for (char c : key) hash = hash * 17 + static_cast<unsigned char>(c);
        return 1 + (hash % (_size - 1));
    }

public:
    HashTableDoubleHashing(size_t s = 101) : _size(s) { _rows.resize(_size); }

    void insert(const std::string& key, const Tvalue& value) override {
        if (_count >= _size) throw std::overflow_error("Table full");
        size_t idx = h1(key), step = h2(key), start = idx;
        while (_rows[idx]._state == HashDate<Tvalue>::BUSY) {
            if (_rows[idx]._key == key) throw std::logic_error("Key exists");
            idx = (idx + step) % _size;
            if (idx == start) throw std::overflow_error("No space");
        }
        _rows[idx] = { HashDate<Tvalue>::BUSY, key, value };
        _count++;
    }

    void erase(const std::string& key) override {
        size_t idx = h1(key), step = h2(key), start = idx;
        while (_rows[idx]._state != HashDate<Tvalue>::EMPTY) {
            if (_rows[idx]._state == HashDate<Tvalue>::BUSY && _rows[idx]._key == key) {
                _rows[idx]._state = HashDate<Tvalue>::DELETED;
                _count--; return;
            }
            idx = (idx + step) % _size;
            if (idx == start) break;
        }
        throw std::logic_error("Not found");
    }

    Tvalue& find(const std::string& key) override {
        size_t idx = h1(key), step = h2(key), start = idx;
        while (_rows[idx]._state != HashDate<Tvalue>::EMPTY) {
            if (_rows[idx]._state == HashDate<Tvalue>::BUSY && _rows[idx]._key == key) return _rows[idx]._data;
            idx = (idx + step) % _size;
            if (idx == start) break;
        }
        throw std::logic_error("Not found");
    }

    void replace(const std::string& key, const Tvalue& value) override { find(key) = value; }

    bool consist(const std::string& key) const noexcept override {
        size_t idx = h1(key), step = h2(key), start = idx;
        while (_rows[idx]._state != HashDate<Tvalue>::EMPTY) {
            if (_rows[idx]._state == HashDate<Tvalue>::BUSY && _rows[idx]._key == key) return true;
            idx = (idx + step) % _size;
            if (idx == start) break;
        }
        return false;
    }

    bool is_empty() const noexcept override { return _count == 0; }

    std::ostream& print(std::ostream& os) const noexcept override {
        for (size_t i = 0; i < _size; ++i) if (_rows[i]._state == HashDate<Tvalue>::BUSY) os << _rows[i]._key << "\n";
        return os;
    }
};
