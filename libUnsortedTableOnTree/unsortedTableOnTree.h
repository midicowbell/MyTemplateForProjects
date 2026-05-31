#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../libTree/tree.h"
#include "list.h"
template <typename Tkey, typename Tvalue>
class UnsortedTableOnTree : public Itable<Tkey, Tvalue> {
private:
    Tree<Tkey, Tvalue> _tree;

public:
    UnsortedTableOnTree() = default;
    ~UnsortedTableOnTree() override = default;

    void insert(const Tkey& key, const Tvalue& value) override {
        if (consist(key)) {
            throw std::runtime_error("Insert error: Duplicate key exception!");
        }
        _tree.insert(key, value);
    }

    void replace(const Tkey& key, const Tvalue& value) override {
        const Tvalue* res = _tree.find(key);
        if (res == nullptr) {
            throw std::runtime_error("Replace error: Key not found!");
        }
        const_cast<Tvalue&>(*res) = value;
    }
    Tvalue& find(const Tkey& key) override {
        const Tvalue* res = _tree.find(key);
        if (res == nullptr) {
            throw std::runtime_error("Find error: Key not found!");
        }
        return const_cast<Tvalue&>(*res);
    }
    void erase(const Tkey& key) override {
        _tree.remove(key);
    }

    bool is_empty() const noexcept override {
        return _tree.is_empty();
    }

    bool consist(const Tkey& key) const noexcept override {
        return _tree.find(key) != nullptr;
    }
    std::ostream& print(std::ostream& os) const noexcept override {
        if (is_empty()) {
            os << "Table is empty.";
            return os;
        }

        _tree.width();
        return os;
    }
};