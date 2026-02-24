#pragma once

#include <iostream>
#include <stdexcept>

template<typename T>
class List {
private:
    template<typename U>
    struct Node {
        U value;
        Node<U>* next;

        Node(U val, Node<U>* nxt = nullptr) : value(val), next(nxt) {}
    };

    Node<T>* _head;
    Node<T>* _tail;
    int _count;

    Node<T>* get_node_at(int position) const {
        if (position < 0 || position >= _count) {
            throw std::out_of_range("Position out of range");
        }

        Node<T>* current = _head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        return current;
    }

public:
    class Iterator {
        Node<T>* current;
    public:
        Iterator() : current(nullptr) {}
        Iterator(Node<T>* pos) : current(pos) {}
        Iterator(const Iterator& other) : current(other.current) {}

        Iterator& operator=(const Iterator& other) {
            current = other.current;
            return *this;
        }

        T& operator*() {
            return current->value;
        }

        bool operator!=(const Iterator& other) {
            return current != other.current;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            current = current->next;
            return temp;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }
    };

    typedef Iterator iterator;

    List() : _head(nullptr), _tail(nullptr), _count(0) {}

    List(const List& other) : _head(nullptr), _tail(nullptr), _count(0) {
        Node<T>* current = other._head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }

    ~List() {
        clear();
    }

    Iterator begin() {
        return Iterator(_head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
    Iterator begin() const {
        return Iterator(_head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
    void push_front(const T& val) {
        Node<T>* new_node = new Node<T>(val, _head);

        if (is_empty()) {
            _head = _tail = new_node;
        }
        else {
            _head = new_node;
        }
        _count++;
    }

    void push_back(const T& val) {
        Node<T>* new_node = new Node<T>(val);

        if (is_empty()) {
            _head = _tail = new_node;
        }
        else {
            _tail->next = new_node;
            _tail = new_node;
        }
        _count++;
    }

    void insert(int pos, const T& val) {
        if (pos < 0 || pos > _count) {
            throw std::out_of_range("Position out of range");
        }

        if (pos == 0) {
            push_front(val);
        }
        else if (pos == _count) {
            push_back(val);
        }
        else {
            Node<T>* prev_node = get_node_at(pos - 1);
            Node<T>* new_node = new Node<T>(val, prev_node->next);
            prev_node->next = new_node;

            if (new_node->next == nullptr) {
                _tail = new_node;
            }
            _count++;
        }
    }

    void insert(Node<T>* node, const T& val) {
        if (node == nullptr) {
            push_back(val);
            return;
        }

        if (node == _head) {
            push_front(val);
        }
        else {
            Node<T>* prev = _head;
            while (prev != nullptr && prev->next != node) {
                prev = prev->next;
            }

            if (prev != nullptr) {
                Node<T>* new_node = new Node<T>(val, node);
                prev->next = new_node;
                _count++;
            }
        }
    }

    void pop_front() {
        if (is_empty()) {
            throw std::runtime_error("Cannot pop from empty list");
        }

        Node<T>* temp = _head;
        _head = _head->next;

        if (_head == nullptr) {
            _tail = nullptr;
        }

        delete temp;
        _count--;
    }

    void pop_back() {
        if (is_empty()) {
            throw std::runtime_error("Cannot pop from empty list");
        }

        if (_head == _tail) {
            delete _head;
            _head = _tail = nullptr;
        }
        else {
            Node<T>* current = _head;
            while (current->next != _tail) {
                current = current->next;
            }

            delete _tail;
            _tail = current;
            _tail->next = nullptr;
        }
        _count--;
    }

    void erase(int pos) {
        if (is_empty()) {
            throw std::runtime_error("Cannot erase from empty list");
        }

        if (pos < 0 || pos >= _count) {
            throw std::out_of_range("Position out of range");
        }

        if (pos == 0) {
            pop_front();
        }
        else {
            Node<T>* prev_node = get_node_at(pos - 1);
            Node<T>* node_to_delete = prev_node->next;

            prev_node->next = node_to_delete->next;

            if (node_to_delete == _tail) {
                _tail = prev_node;
            }

            delete node_to_delete;
            _count--;
        }
    }

    void erase(Node<T>* node) {
        if (node == nullptr || is_empty()) {
            return;
        }

        if (node == _head) {
            pop_front();
        }
        else {
            Node<T>* prev = _head;
            while (prev != nullptr && prev->next != node) {
                prev = prev->next;
            }

            if (prev != nullptr) {
                prev->next = node->next;

                if (node == _tail) {
                    _tail = prev;
                }

                delete node;
                _count--;
            }
        }
    }

    bool is_empty() const {
        return _head == nullptr;
    }

    int size() const {
        return _count;
    }

    Node<T>* find(const T& val) {
        Node<T>* current = _head;
        while (current != nullptr) {
            if (current->value == val) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    const Node<T>* find(const T& val) const {
        Node<T>* current = _head;
        while (current != nullptr) {
            if (current->value == val) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void clear() {
        while (!is_empty()) {
            pop_front();
        }
    }
    T& front() {
        if (is_empty()) throw std::logic_error("List is empty");
        return _head->value;
    }
};