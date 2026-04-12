#pragma once
#include <utility>
template<typename Tkey, typename Tvalue>
struct AVLNode
{
	std::pair<Tkey, Tvalue> _data;
	AVLNode* _left, * _right, * _parent;
	size_t _height;
};

template<typename Tkey, typename Tvalue>
class AVLTree {
private:
	AVLNode<Tkey, Tvalue>* _root;
    void clear(AVLNode<Tkey, Tvalue>* node) {
        if (node != nullptr) {
            clear(node->_left);
            clear(node->_right);
            delete node;
        }
    }
    void left_rotate(AVLNode<Tkey, Tvalue>* G) {
        AVLNode<Tkey, Tvalue>* P = G->_right;
        G->_right = P->_left;

        if (P->_left != nullptr) {
            P->_left->_parent = G;
        }
        P->_left = G;
        P->_parent = G->_parent;
        if (G->_parent != nullptr) {
            if (G->_parent->_left == G) G->_parent->_left = P;
            else G->_parent->_right = P;
        }
        else {
            _root = P;
        }

        G->_parent = P;
        recalc_height(G);
        recalc_height(P);
    }
    void right_rotate(AVLNode<Tkey, Tvalue>* G) {
        AVLNode<Tkey, Tvalue>* P = G->_left;
        G->_left = P->_right;
        if (P->_right != nullptr) {
            P->_right->_parent = G;
        }
        P->_right = G;
        P->_parent = G->_parent;
        if (G->_parent != nullptr) {
            if (G->_parent->_right == G) G->_parent->_right = P;
            else G->_parent->_left = P;
        }
        else {
            _root = P;
        }

        G->_parent = P;

        recalc_height(G);
        recalc_height(P);
    }

    int get_balance(AVLNode<Tkey, Tvalue>* node) const {
        if (node == nullptr) {
            return 0;
        }
        return get_height(node->_right) - get_height(node->_left);
    }
    void recalc_height(AVLNode<Tkey, Tvalue>* node) {
        if (node != nullptr) {
            int left_h = get_height(node->_left);
            int right_h = get_height(node->_right);
            if (left_h > right_h) {
                node->_height = left_h + 1;
            }
            else {
                node->_height = right_h + 1;
            }
        }
    }
    void balance(AVLNode<Tkey, Tvalue>* node) {
        if (node == nullptr) return;
        recalc_height(node);
        int bal = get_balance(node);
        if (bal == 2) {
            if (get_balance(node->_right) < 0) {
                right_rotate(node->_right); // сучай RL
            }
            left_rotate(node); // случай RR
        }
        else if (bal == -2) {
            if (get_balance(node->_left) > 0) {
                left_rotate(node->_left); // случай LR
            }
            right_rotate(node); // случай LL
        }
    }
    int get_height(AVLNode<Tkey, Tvalue>* node) const {
        if (node == nullptr) {
            return 0;
        }
        else {
            return node->_height;
        }
    }

public:
	AVLTree() : _root(nullptr) {}
	bool is_empty() const noexcept {
		return _root == nullptr;
	}
    ~AVLTree() {
        clear(_root);
    }
    
    void insert(const Tkey& key, const Tvalue& val) {
        if (_root == nullptr) {
            _root = new AVLNode<Tkey, Tvalue>{ { key, val }, nullptr, nullptr, nullptr, 1 };
            return;
        }

        AVLNode<Tkey, Tvalue>* pCurrent = _root;
        AVLNode<Tkey, Tvalue>* pParent = nullptr;

        while (pCurrent != nullptr) {
            pParent = pCurrent;
            if (key < pCurrent->_data.first) {
                pCurrent = pCurrent->_left;
            }
            else if (key > pCurrent->_data.first) {
                pCurrent = pCurrent->_right;
            }
            else {
                return; 
            }
        }
        AVLNode<Tkey, Tvalue>* pNew = new AVLNode<Tkey, Tvalue>{ {key, val}, nullptr, nullptr, pParent, 1 };

        if (key < pParent->_data.first) {
            pParent->_left = pNew;
        }
        else {
            pParent->_right = pNew;
        }

        AVLNode<Tkey, Tvalue>* pBalance = pParent;
        while (pBalance != nullptr) {
            balance(pBalance);
            pBalance = pBalance->_parent; 
        }
    }
    Tvalue* find(const Tkey& key) {
        AVLNode<Tkey, Tvalue>* pCurrent = _root;

        while (pCurrent != nullptr) {
            if (key == pCurrent->_data.first) {
                return &(pCurrent->_data.second);
            }

            if (key < pCurrent->_data.first) {
                pCurrent = pCurrent->_left;
            }
            else {
                pCurrent = pCurrent->_right;
            }
        }
        return nullptr;
    }
    int height() const { return get_height(_root); }
    void remove(const Tkey& key) {
        AVLNode<Tkey, Tvalue>* pNode = _root;
        while (pNode != nullptr && pNode->_data.first != key) {
            if (key < pNode->_data.first) pNode = pNode->_left;
            else pNode = pNode->_right;
        }

        if (pNode == nullptr) return;

        AVLNode<Tkey, Tvalue>* pDelete = nullptr;
        if (pNode->_left == nullptr || pNode->_right == nullptr) {
            pDelete = pNode; 
        }
        else {
            pDelete = pNode->_right;
            while (pDelete->_left != nullptr) pDelete = pDelete->_left;

            pNode->_data = pDelete->_data;
        }
        AVLNode<Tkey, Tvalue>* pChild = (pDelete->_left != nullptr) ? pDelete->_left : pDelete->_right;
        AVLNode<Tkey, Tvalue>* pBalanceStart = pDelete->_parent;

        if (pChild != nullptr) {
            pChild->_parent = pDelete->_parent;
        }

        if (pDelete->_parent == nullptr) {
            _root = pChild;
        }
        else {
            if (pDelete->_parent->_left == pDelete) {
                pDelete->_parent->_left = pChild;
            }
            else {
                pDelete->_parent->_right = pChild;
            }
        }

        delete pDelete;
        AVLNode<Tkey, Tvalue>* pTemp = pBalanceStart;
        while (pTemp != nullptr) {
            balance(pTemp); 
            pTemp = pTemp->_parent;
        }
    }
};
