#pragma once

#include <iostream>
#include <stdexcept>

template<typename T>
class ListDoubly {
private:
    template<typename U>
    struct Node {
        U value;
        Node<U>* next;
        Node<U>* prev;

        Node(U val, Node<U>* nxt = nullptr, Node<U>* pre = nullptr) : value(val), next(nxt), prev(pre) {}
    };

    Node<T>* _head;
    Node<T>* _tail;
    int _count;

    Node<T>* get_node_at(int position) const {
        if (position < 0 || position >= _count) {
            throw std::logic_error("Position out of range");
        }

        Node<T>* current = _head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        return current;
    }

public:
    class Iterator {
    private:
        Node<T>* current;
    public:
        friend class ListDoubly<T>;
        Iterator() : current(nullptr) {}
        Iterator(Node<T>* pos) : current(pos) {}
        Iterator(const Iterator& other) : current(other.current) {}

        Iterator& operator=(const Iterator& other) {
            current = other.current;
            return *this;
        }
        T* operator->() {
            return &current->value;
        }
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        T& operator*() {
            if (current == nullptr) {
                throw std::logic_error("Dereferencing end iterator");
            }
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
        Iterator operator--(int) {
            Iterator temp = *this;
            current = current->prev;
            return temp;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }
        Iterator& operator--() {
            current = current->prev;
            return *this;
        }
    };

    typedef Iterator iterator;

    ListDoubly() : _head(nullptr), _tail(nullptr), _count(0) {};
    ListDoubly(const ListDoubly<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(*it);
        }
    }
    ListDoubly<T>& operator=(const ListDoubly<T>& other) {
        if (this != &other) {
            clear();
            for (auto it = other.begin(); it != other.end(); ++it) {
                push_back(*it);
            }
        }
        return *this;
    }

    ~ListDoubly() {
        clear();
    }

    Iterator begin() {
        return Iterator(_head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
    Iterator begin()const {
        return Iterator(_head);
    }

    Iterator end()const {
        return Iterator(nullptr);
    }

    void push_front(const T& val) {
        Node<T>* new_node = new Node<T>(val, _head);

        if (is_empty()) {
            _head = _tail = new_node;
        }
        else {
            _head->prev = new_node;
            _head = new_node;
        }
        _count++;
    }

    void push_back(const T& val) {
        Node<T>* new_node = new Node<T>(val, nullptr, _tail);

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
            throw std::logic_error("Position out of range");
        }

        if (pos == 0) {
            push_front(val);
        }
        else if (pos == _count) {
            push_back(val);
        }
        else {
            Node<T>* curr = get_node_at(pos);
            insert(curr, val);
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
            Node<T>* new_node = new Node<T>(val, node, node->prev);
            node->prev->next = new_node;
            node->prev = new_node;
            _count++;
        }
    }

    void pop_front() {
        if (is_empty()) {
            throw std::logic_error("Cannot pop from empty list");
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
            throw std::logic_error("Cannot pop from empty list");
        }

        if (_head == _tail) {
            delete _head;
            _head = _tail = nullptr;
        }
        else {
            _tail = _tail->prev;
            delete _tail->next;
            _tail->next = nullptr;
        }
        _count--;
    }
    void erase(Iterator it);
    void erase(int pos) {
        if (is_empty()) {
            throw std::logic_error("Cannot erase from empty list");
        }

        if (pos < 0 || pos >= _count) {
            throw std::logic_error("Position out of range");
        }

        if (pos == 0) {
            pop_front();
        }
        else if (pos == _count - 1) { pop_back(); }
        else {
            Node<T>* curr = get_node_at(pos);
            erase(curr);
        }

    }

    void erase(Node<T>* node) {
        if (node == nullptr || is_empty()) {
            return;
        }

        if (node == _head) {
            pop_front();
        }
        else if (node == _tail) {
            pop_back();
        }
        else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            delete node;
            _count--;
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
};
template<typename T>
void ListDoubly<T>::erase(Iterator it) {
    erase(it.current);
}
