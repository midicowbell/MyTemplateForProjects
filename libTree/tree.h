#pragma once
#include <iostream>
#include <queue>

template<typename Tkey, typename Tvalue>
struct Node {
    std::pair<Tkey, Tvalue> data;
    Node* left;
    Node* right;
public:
    Node(const Tkey& key, const Tvalue& value)
        : data(key, value), left(nullptr), right(nullptr) {
    }
    Node() : data(), left(nullptr), right(nullptr) {}
};

template<typename Tkey, typename Tvalue>
class Tree {
private:
    Node<Tkey, Tvalue>* _root;
    void lcr_rec(Node<Tkey, Tvalue>* node) const {
        if (node == nullptr) return;
        lcr_rec(node->left);
        std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
        lcr_rec(node->right);
    }
    void lrc_rec(Node<Tkey, Tvalue>* node) const {
        if (node == nullptr) return;
        lrc_rec(node->left);
        lrc_rec(node->right);
        std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
    }
    void clr_rec(Node<Tkey, Tvalue>* node) const {
        if (node == nullptr) return;
        std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
        clr_rec(node->left);
        clr_rec(node->right);
    }
    void width_rec() const {
        if (is_empty()) {
            std::cout << "Width: Tree is empty" << std::endl;
            return;
        }
        std::queue<Node<Tkey, Tvalue>*> q;
        q.push(_root);
        int level = 0;
        while (!q.empty()) {
            int levelSize = q.size();
            std::cout << "Level " << level << ": ";
            for (int i = 0; i < levelSize; i++) {
                Node<Tkey, Tvalue>* node = q.front();
                q.pop();
                std::cout << "(" << node->data.first << ":" << node->data.second << ") ";
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            std::cout << std::endl;
            level++;
        }
    }
    Node<Tkey, Tvalue>* find_rec(Node<Tkey, Tvalue>* node, const Tkey& key) const {
        if (node == nullptr) return nullptr;
        if (key == node->data.first) return node;
        if (key < node->data.first)  return find_rec(node->left, key);
        else                         return find_rec(node->right, key);
    }
    Node<Tkey, Tvalue>* find_min(Node<Tkey, Tvalue>* node) const {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    Node<Tkey, Tvalue>* remove_rec(Node<Tkey, Tvalue>* node, const Tkey& key) {
        if (node == nullptr) return nullptr;

        if (key < node->data.first) {
            node->left = remove_rec(node->left, key);
        }
        else if (key > node->data.first) {
            node->right = remove_rec(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                Node<Tkey, Tvalue>* tmp = node->right;
                delete node;
                return tmp;
            }
            else if (node->right == nullptr) {
                Node<Tkey, Tvalue>* tmp = node->left;
                delete node;
                return tmp;
            }
            else {
                Node<Tkey, Tvalue>* successor = find_min(node->right);
                node->data = successor->data;
                node->right = remove_rec(node->right, successor->data.first);
            }
        }
        return node;
    }

    void deleteTree(Node<Tkey, Tvalue>* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    Tree() : _root(nullptr) {}
    ~Tree() { deleteTree(_root); }

    void insert(const Tkey& key, const Tvalue& value) {
        if (_root == nullptr) {
            _root = new Node<Tkey, Tvalue>(key, value);
            return;
        }
        std::queue<Node<Tkey, Tvalue>*> q;
        q.push(_root);
        while (!q.empty()) {
            Node<Tkey, Tvalue>* node = q.front();
            q.pop();
            if (key < node->data.first) {
                if (!node->left) { node->left = new Node<Tkey, Tvalue>(key, value); return; }
                else              q.push(node->left);
            }
            else if (key > node->data.first) {
                if (!node->right) { node->right = new Node<Tkey, Tvalue>(key, value); return; }
                else               q.push(node->right);
            }
            else {
                node->data.second = value;
                return;
            }
        }
    }

    const Tvalue* find(const Tkey& key) const {
        Node<Tkey, Tvalue>* result = find_rec(_root, key);
        if (result == nullptr) return nullptr;
        return &result->data.second;
    }

    void remove(const Tkey& key) {
        _root = remove_rec(_root, key);
    }

    bool is_empty() const { return _root == nullptr; }

    void lcr() const {
        std::cout << "LCR (Левое → Корень → Правое): ";
        lcr_rec(_root);
        std::cout << std::endl;
    }
    void lrc() const {
        std::cout << "LRC (Левое → Правое → Корень): ";
        lrc_rec(_root);
        std::cout << std::endl;
    }
    void clr() const {
        std::cout << "CLR (Корень → Левое → Правое): ";
        clr_rec(_root);
        std::cout << std::endl;
    }
    void width() const {
        std::cout << "WIDTH (В ШИРИНУ):" << std::endl;
        width_rec();
    }
};