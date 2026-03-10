#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../libTvector/tvector.h"
#include "../libITable/itable.h"

template <typename Tkey, typename Tvalue>
class UnsortedTableOnVec : public Itable<Tkey, Tvalue> {
private:
    Tvector<std::pair<Tkey, Tvalue>> _rows;

    // Вспомогательный метод для поиска индекса (используется несколько раз)
    int _findIndex(const Tkey& key) const noexcept {
        for (size_t i = 0; i < _rows.size(); i++) {
            if (_rows[i].first == key) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

public:
    UnsortedTableOnVec() = default;
    virtual ~UnsortedTableOnVec() = default;
    void insert(const Tkey& key, const Tvalue& value) override {
        if (consist(key)) {
            throw std::logic_error("Key already exists");
        }
        _rows.push_back({ key, value });
    }

    void replace(const Tkey& key, const Tvalue& value) override {
        int idx = _findIndex(key);
        if (idx != -1) {
            _rows[idx].second = value;
        }
        else {
            _rows.push_back({ key, value });
        }
    }

    Tvalue& find(const Tkey& key) override {
        int idx = _findIndex(key);
        if (idx != -1) {
            return _rows[idx].second;
        }
        throw std::out_of_range("Key not found");
    }

    void erase(const Tkey& key) override {
        int idx = _findIndex(key);
        if (idx != -1) {
            _rows.erase(static_cast<size_t>(idx), 1);
        }
    }

    bool consist(const Tkey& key) const noexcept override {
        return _findIndex(key) != -1;
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