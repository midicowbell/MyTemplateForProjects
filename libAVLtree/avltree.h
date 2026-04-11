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
public:
	AVLTree() : _root(nullptr) {}
	bool is_empty() const noexcept {
		return _root == nullptr;
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

        G->parent = P;
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
    int get_height(AVLNode<Tkey, Tvalue>* node) const {
        if (node == nullptr) {
            return 0;
        }
        else {
            return node->_height;
        }
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

};
