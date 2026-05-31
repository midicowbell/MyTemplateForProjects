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
        Node<Tkey, Tvalue>* newNode = new Node<Tkey, Tvalue>(key, value);

        if (_root == nullptr) {
            _root = newNode;
            return;
        }

        std::queue<Node<Tkey, Tvalue>*> q;
        q.push(_root);

        while (!q.empty()) {
            Node<Tkey, Tvalue>* cur = q.front();
            q.pop();

            if (!cur->left) {
                cur->left = newNode;
                return;
            }
            else {
                q.push(cur->left);
            }

            if (!cur->right) {
                cur->right = newNode;
                return;
            }
            else {
                q.push(cur->right);
            }
        }
    }
    const Tvalue* find(const Tkey& key) const {
        if (_root == nullptr) return nullptr;

        std::queue<Node<Tkey, Tvalue>*> q;
        q.push(_root);

        while (!q.empty()) {
            Node<Tkey, Tvalue>* cur = q.front();
            q.pop();

            if (cur->data.first == key) {
                return &cur->data.second;
            }

            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        return nullptr;
    }

    void remove(const Tkey& key) {
        if (_root == nullptr) return;
    
        if (_root->left == nullptr && _root->right == nullptr) {
            if (_root->data.first == key) {
                delete _root;
                _root = nullptr;
            }
            return;
        }

        std::queue<Node<Tkey, Tvalue>*> q;
        q.push(_root);

        Node<Tkey, Tvalue>* targetNode = nullptr;
        Node<Tkey, Tvalue>* deepestNode = _root;
        Node<Tkey, Tvalue>* parentOfDeepest = nullptr;

        
        while (!q.empty()) {
            Node<Tkey, Tvalue>* cur = q.front();
            q.pop();

            if (cur->data.first == key) {
                targetNode = cur;
            }

            if (cur->left) {
                parentOfDeepest = cur;
                deepestNode = cur->left;
                q.push(cur->left);
            }
            if (cur->right) {
                parentOfDeepest = cur;
                deepestNode = cur->right;
                q.push(cur->right);
            }
        }
        if (targetNode != nullptr) {
            targetNode->data = deepestNode->data;
            if (parentOfDeepest->right == deepestNode) {
                parentOfDeepest->right = nullptr;
            }
            else if (parentOfDeepest->left == deepestNode) {
                parentOfDeepest->left = nullptr;
            }
            delete deepestNode;
        }
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