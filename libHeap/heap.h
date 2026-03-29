#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

template<typename T>
class MinHeap {
private:
    std::vector<T> _data;
    void sift_down(int i) {
        int size = _data.size();
        while (true) {
            int leftChild = 2 * i + 1;
            int rightChild = 2 * i + 2;
            int minChild = i;

            if (leftChild < size && _data[leftChild] < _data[minChild]) {
                minChild = leftChild;
            }
            if (rightChild < size && _data[rightChild] < _data[minChild]) {
                minChild = rightChild;
            }
            if (minChild == i) {
                break;
            }
            std::swap(_data[i], _data[minChild]);
            i = minChild;
        }
    }
    void sift_up(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (_data[i] < _data[parent]) {
                std::swap(_data[i], _data[parent]);
                i = parent;
            }
            else {
                break;
            }
        }
    }

public:
    MinHeap() = default;

    size_t size() const {
        return _data.size();
    }

    bool empty() const {
        return _data.empty();
    }
    void add(const T& value) {
        _data.push_back(value);
        sift_up(_data.size() - 1);
    }
    T pop() {
        if (_data.empty()) {
            throw std::logic_error("Heap is empty");
        }
        T root = _data[0];
        _data[0] = _data.back();
        _data.pop_back();
        if (!_data.empty()) {
            sift_down(0);
        }
        return root;
    }
};