#pragma once
#include <iostream>
#include <queue>
#include <stdexcept>
#include <utility>

template<typename Tkey, typename Tvalue>
struct Node {
    std::pair<Tkey, Tvalue> data;
    Node<Tkey, Tvalue>* left;
    Node<Tkey, Tvalue>* right;

    Node(const Tkey& key, const Tvalue& value)
        : data(key, value), left(nullptr), right(nullptr) {
    }
};

template<typename Tkey, typename Tvalue>
class Tree {
private:
    Node<Tkey, Tvalue>* _root;

    void lcr_rec(Node<Tkey, Tvalue>* node) const {
        if (!node) return;
        lcr_rec(node->left);
        std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
        lcr_rec(node->right);
    }

    void lrc_rec(Node<Tkey, Tvalue>* node) const {
        if (!node) return;
        lrc_rec(node->left);
        lrc_rec(node->right);
        std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
    }

    void clr_rec(Node<Tkey, Tvalue>* node) const {
        if (!node) return;
        std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
        clr_rec(node->left);
        clr_rec(node->right);
    }

    void deleteTree(Node<Tkey, Tvalue>* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    Node<Tkey, Tvalue>* find_parent(const Tkey& key) const {
        if (!_root || _root->data.first == key) return _root;

        Node<Tkey, Tvalue>* curr = _root;
        Node<Tkey, Tvalue>* parent = nullptr;

        while (curr != nullptr) {
            if (curr->data.first == key) return parent;

            parent = curr;
            if (key < curr->data.first)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return parent;
    }

public:
    Tree() : _root(nullptr) {}
    ~Tree() { deleteTree(_root); }

    bool is_empty() const { return _root == nullptr; }

    Tvalue* find(const Tkey& key) {
        Node<Tkey, Tvalue>* curr = _root;
        while (curr) {
            if (curr->data.first == key) return &(curr->data.second);
            if (key < curr->data.first) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }

    void insert(const Tkey& key, const Tvalue& value) {
        if (!_root) {
            _root = new Node<Tkey, Tvalue>(key, value);
            return;
        }
        Node<Tkey, Tvalue>* parent = find_parent(key);
        if (parent->data.first == key ||
            (parent->left && parent->left->data.first == key) ||
            (parent->right && parent->right->data.first == key)) {
            throw std::logic_error("The key is already in use");
        }

        if (key < parent->data.first) {
            parent->left = new Node<Tkey, Tvalue>(key, value);
        }
        else {
            parent->right = new Node<Tkey, Tvalue>(key, value);
        }
    }

    // Обходы
    void lcr() const {
        std::cout << "LCR: ";
        lcr_rec(_root);
        std::cout << std::endl;
    }

    void lrc() const {
        std::cout << "LRC: ";
        lrc_rec(_root);
        std::cout << std::endl;
    }

    void clr() const {
        std::cout << "CLR: ";
        clr_rec(_root);
        std::cout << std::endl;
    }

    void width() const {
        std::cout << "WIDTH:" << std::endl;
        if (is_empty()) return;

        std::queue<Node<Tkey, Tvalue>*> q;
        q.push(_root);
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            std::cout << "Level " << level << ": ";
            for (int i = 0; i < size; ++i) {
                Node<Tkey, Tvalue>* node = q.front();
                q.pop();
                std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            std::cout << std::endl;
            level++;
        }
    }
};