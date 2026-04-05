#pragma once
#include <utility>
template<typename Tkey, typename Tvalue>
struct AVLNode
{
	std::pair<Tkey, Tvalue> _data;
	AVLNode* _left, * _right, * _parent;
	size_t _data;
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
    void left_rotate(BSTNode<Tkey, Tvalue>* G) {
        BSTNode<Tkey, Tvalue>* P = G->right;
        G->right = P->left;

        if (P->left != nullptr) {
            P->left->parent = G;
        }
        P->left = G;
        P->parent = G->parent;
        if (G->parent != nullptr) {
            if (G->parent->left == G) G->parent->left = P;
            else G->parent->right = P;
        }
        else {
            _root = P;
        }

        G->parent = P;
    }

};
