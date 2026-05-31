#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <list> 
#include "../libTvector/tvector.h"
#include "../libITable/itable.h"
#include <vector>

template<typename Tvalue>
struct ChainNode {
    std::string _key;
    Tvalue _data;
};

template<typename Tvalue>
class HashTableChaining : public Itable<std::string, Tvalue> {
private:
    std::vector<std::list<ChainNode<Tvalue>>> _rows;
    size_t _size;
    size_t _count = 0;

    size_t h(const std::string& key) const {
        size_t hash = 0;
        for (char c : key) hash = hash * 31 + static_cast<unsigned char>(c);
        return hash % _size;
    }

public:
    HashTableChaining(size_t s = 101) : _size(s) { _rows.resize(_size); }

    void insert(const std::string& key, const Tvalue& value) override {
        size_t idx = h(key);
        for (auto& n : _rows[idx]) if (n._key == key) throw std::logic_error("Exists");
        _rows[idx].push_back({ key, value });
        _count++;
    }

    void erase(const std::string& key) override {
        size_t idx = h(key);
        auto& chain = _rows[idx];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->_key == key) { chain.erase(it); _count--; return; }
        }
        throw std::logic_error("Not found");
    }

    Tvalue& find(const std::string& key) override {
        size_t idx = h(key);
        for (auto& n : _rows[idx]) if (n._key == key) return n._data;
        throw std::logic_error("Not found");
    }

    void replace(const std::string& key, const Tvalue& value) override { find(key) = value; }

    bool consist(const std::string& key) const noexcept override {
        size_t idx = h(key);
        for (const auto& n : _rows[idx]) if (n._key == key) return true;
        return false;
    }

    bool is_empty() const noexcept override { return _count == 0; }

    std::ostream& print(std::ostream& os) const noexcept override {
        for (size_t i = 0; i < _size; ++i) for (auto& n : _rows[i]) os << n._key << "\n";
        return os;
    }
};

