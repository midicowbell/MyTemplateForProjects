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
struct HashDate {
    enum States { EMPTY, BUSY, DELETED };
    States _state = EMPTY;
    std::string _key = "";
    Tvalue _data = {};
};

template<typename Tvalue>
class HashTableOA : public Itable<std::string, Tvalue> {
private:
    Tvector<HashDate<Tvalue>> _rows;
    size_t _size = SIZE;
    size_t _count = 0;
    size_t _shift = SHIFT;

    size_t h(const std::string& key) const {
        size_t hash = 0;
        for (size_t i = 0; i < key.length(); i++) {
            hash += static_cast<unsigned char>(key[i]);
        }
        return hash % _size;
    }

    size_t hh(size_t hash) const {
        return (hash + _shift) % _size;
    }

    bool is_simple(size_t a, size_t b) const {
        while (b) {
            a %= b;
            std::swap(a, b);
        }
        return a == 1;
    }

public:
    HashTableOA() : _size(SIZE), _shift(SHIFT) {
        _rows.resize(_size);
    }

    HashTableOA(size_t s) : _size(s) {
        _rows.resize(_size);
        for (size_t i = std::max(static_cast<size_t>(2), _size / 15); i < _size; i++) {
            if (is_simple(i, _size)) {
                _shift = i;
            }
        }
    }

    void insert(const std::string& key, const Tvalue& value) override {
        if (_count >= _size) return;

        size_t hash = h(key);
        size_t start_hash = hash;
        while (true) {
            if (_rows[hash]._state != HashDate<Tvalue>::BUSY) {
                _rows[hash]._state = HashDate<Tvalue>::BUSY;
                _rows[hash]._data = value;
                _rows[hash]._key = key;
                _count++;
                return;
            }
            if (_rows[hash]._key == key) {
                throw std::logic_error("Key already exists");
            }
            hash = hh(hash);
            if (hash == start_hash) break;
        }
    }

    void erase(const std::string& key) override {
        size_t hash = h(key);
        size_t first_hash = hash;
        while (true) {
            if (_rows[hash]._state == HashDate<Tvalue>::EMPTY) break;

            if (_rows[hash]._state == HashDate<Tvalue>::BUSY && _rows[hash]._key == key) {
                _rows[hash]._state = HashDate<Tvalue>::DELETED;
                _count--;
                return;
            }
            hash = hh(hash);
            if (first_hash == hash) break;
        }
        throw std::logic_error("Key not found");
    }

    Tvalue& find(const std::string& key) override {
        size_t hash = h(key);
        size_t first_hash = hash;
        while (true) {
            if (_rows[hash]._state == HashDate<Tvalue>::EMPTY) break;

            if (_rows[hash]._state == HashDate<Tvalue>::BUSY && _rows[hash]._key == key) {
                return _rows[hash]._data;
            }
            hash = hh(hash);
            if (first_hash == hash) break;
        }
        throw std::logic_error("Key not found");
    }

    void replace(const std::string& key, const Tvalue& value) override {
        find(key) = value;
    }

    bool consist(const std::string& key) const noexcept override {
        size_t hash = h(key);
        size_t first_hash = hash;
        while (true) {
            if (_rows[hash]._state == HashDate<Tvalue>::EMPTY) return false;
            if (_rows[hash]._state == HashDate<Tvalue>::BUSY && _rows[hash]._key == key) return true;
            hash = hh(hash);
            if (first_hash == hash) break;
        }
        return false;
    }

    bool is_empty() const noexcept override {
        return _count == 0;
    }

    std::ostream& print(std::ostream& os) const noexcept override {
        for (size_t i = 0; i < _size; i++) {
            if (_rows[i]._state == HashDate<Tvalue>::BUSY) {
                os << _rows[i]._key << " " << _rows[i]._data << "\n";
            }
        }
        return os;
    }
};