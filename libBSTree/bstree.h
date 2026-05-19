#pragma once
#include <iostream>
#include <utility>

template<typename Tkey, typename Tvalue>
struct BSTNode
{
    std::pair<Tkey, Tvalue> data;
    BSTNode<Tkey, Tvalue>* left;
    BSTNode<Tkey, Tvalue>* right;
};

template<typename Tkey, typename Tvalue>
class BSTree {
private:
    BSTNode<Tkey, Tvalue>* _root;
    BSTNode<Tkey, Tvalue>* FindNode(const Tkey& key, BSTNode<Tkey, Tvalue>* pNode) const {
        if (pNode == nullptr) {
            return nullptr;
        }
        if (key < pNode->data.first) {
            return FindNode(key, pNode->left);
        }
        if (key > pNode->data.first) {
            return FindNode(key, pNode->right);
        }
        return pNode;
    }
    BSTNode<Tkey, Tvalue>* remove_rec(BSTNode<Tkey, Tvalue>* node, const Tkey& key) {
        if (node == nullptr) return nullptr;

        if (key < node->data.first) {
            node->left = remove_rec(node->left, key); 
        }
        else if (key > node->data.first) {
            node->right = remove_rec(node->right, key); 
        }
        else {

            if (node->left == nullptr) {
                BSTNode<Tkey, Tvalue>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BSTNode<Tkey, Tvalue>* temp = node->left;
                delete node;
                return temp; 
            }
            // оба ребенка 
            BSTNode<Tkey, Tvalue>* minNode = node->right;
            while (minNode->left != nullptr) {
                minNode = minNode->left;
            }

            node->data = minNode->data;
            node->right = remove_rec(node->right, minNode->data.first);
        }

        return node;
    }

public:
    BSTree() : _root(nullptr) {}

    bool is_empty() const noexcept {
        return _root == nullptr;
    }
    Tvalue* find(const Tkey& key) const noexcept {
        BSTNode<Tkey, Tvalue>* pNode = FindNode(key, _root);
        if (pNode == nullptr) {
            return nullptr;
        }
        return &pNode->data.second;
    }

    void insert(const Tkey& key, const Tvalue& val) {
        if (_root == nullptr) {
            _root = new BSTNode<Tkey, Tvalue>{ { key, val }, nullptr, nullptr };
            return;
        }

        BSTNode<Tkey, Tvalue>* pCurrent = _root;
        BSTNode<Tkey, Tvalue>* pParent = nullptr;
        while (pCurrent != nullptr) {
            pParent = pCurrent;
            if (key < pCurrent->data.first) {
                pCurrent = pCurrent->left;
            }
            else if (key > pCurrent->data.first) {
                pCurrent = pCurrent->right;
            }
            else {
                return;
            }
        }
        BSTNode<Tkey, Tvalue>* pNew = new BSTNode<Tkey, Tvalue>{ {key, val}, nullptr, nullptr };
        if (key < pParent->data.first) {
            pParent->left = pNew;
        }
        else {
            pParent->right = pNew;
        }
    }
    void remove(const Tkey& key) {
        _root = remove_rec(_root, key);
    }
};