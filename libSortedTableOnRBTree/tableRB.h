#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../libRBTree/rbtree.h"

template <typename Tkey, typename Tvalue>
class TableRBTree : public Itable<Tkey, Tvalue> {
private:
    RBTree<Tkey, Tvalue> _tree;
public:
    TableRBTree() = default;
    ~TableRBTree() override = default;

    void insert(const Tkey& key, const Tvalue& value) override {
        if (consist(key)) {
            throw std::logic_error("Insert error: Duplicate key exception!");
        }
        _tree.insert(key, value);
    }

    void replace(const Tkey& key, const Tvalue& value) override {
        if (!_tree.consist(key)) {
            throw std::out_of_range("Replace error: Key not found!");
        }
        _tree.replace(key, value);
    }

    Tvalue& find(const Tkey& key) override {
        try {
            return _tree.find(key);
        }
        catch (const std::out_of_range&) {
            throw std::out_of_range("Find error: Key not found!");
        }
    }

    void erase(const Tkey& key) override {
        _tree.erase(key);
    }

    bool is_empty() const noexcept override {
        return _tree.is_empty();
    }

    bool consist(const Tkey& key) const noexcept override {
        return _tree.consist(key);
    }

    std::ostream& print(std::ostream& os) const noexcept override {
        _tree.print(os);
        return os;
    }

    size_t size() const noexcept {
        return 0;
    }
};