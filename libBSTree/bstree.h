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
        BSTNode<Tkey, Tvalue>* pCurrent = _root;
        BSTNode<Tkey, Tvalue>* pParent = nullptr;

        // 1. Поиск удаляемого узла и его родителя
        while (pCurrent != nullptr && pCurrent->data.first != key) {
            pParent = pCurrent;
            if (key < pCurrent->data.first)
                pCurrent = pCurrent->left;
            else
                pCurrent = pCurrent->right;
        }

        if (pCurrent == nullptr) return;

        // 2. Случай: У узла два потомка
        if (pCurrent->left != nullptr && pCurrent->right != nullptr) {
            BSTNode<Tkey, Tvalue>* pSuccessor = pCurrent->right;
            BSTNode<Tkey, Tvalue>* pSuccessorParent = pCurrent;

            while (pSuccessor->left != nullptr) {
                pSuccessorParent = pSuccessor;
                pSuccessor = pSuccessor->left;
            }

            pCurrent->data = pSuccessor->data;
            pParent = pSuccessorParent;
            pCurrent = pSuccessor;
        }

        // 3. Случай: У узла один потомок или он — лист [4, 5]
        BSTNode<Tkey, Tvalue>* pChild = (pCurrent->left != nullptr) ? pCurrent->left : pCurrent->right;

        if (pParent == nullptr) {
            _root = pChild;
        }
        else {
            if (pParent->left == pCurrent)
                pParent->left = pChild;
            else
                pParent->right = pChild;
        }

        delete pCurrent;
    }
};