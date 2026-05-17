#pragma once
#include <utility>
#include <iostream>

enum Color { RED, BLACK };

template<typename Tkey, typename Tvalue>
struct RBTreeNode {
    std::pair<Tkey, Tvalue> data;
    Color color;
    int black_height;
    RBTreeNode* left, * right, * parent;

    RBTreeNode(Tkey k, Tvalue v)
        : data(std::make_pair(k, v)), color(RED), black_height(0),
        left(nullptr), right(nullptr), parent(nullptr) {
    }
};

template<typename Tkey, typename Tvalue>
class RBTree {
private:
    void clear(RBTreeNode<Tkey, Tvalue>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    RBTreeNode<Tkey, Tvalue>* root;
    int get_bh(RBTreeNode<Tkey, Tvalue>* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->black_height;
    }
    void recalc_height(RBTreeNode<Tkey, Tvalue>* node) {
        if (node == nullptr) return;
        int child_bh = get_bh(node->left);
        int own_contribution = 0;
        if (node->color == BLACK) {
            own_contribution = 1;
        }

        node->black_height = child_bh + own_contribution;
    }

    /*
     левый поворот:
          (x)             (y)
         /   \           /   \
        A     (y)  ->  (x)    C
             /   \    /   \
            B     C  A     B
     */
    void left_rotate(RBTreeNode<Tkey, Tvalue>* x) {
        RBTreeNode<Tkey, Tvalue>* y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;

        recalc_height(x);
        recalc_height(y);
    }

    /*
      правый поворот:
             (y)           (x)
            /   \         /   \
          (x)    C  ->   A     (y)
         /   \                /   \
        A     B              B     C
     */
    void right_rotate(RBTreeNode<Tkey, Tvalue>* y) {
        RBTreeNode<Tkey, Tvalue>* x = y->left;
        y->left = x->right;

        if (x->right != nullptr) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nullptr) {
            root = x;
        }
        else if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;

        recalc_height(y);
        recalc_height(x);
    }

    void recalc_balance(RBTreeNode<Tkey, Tvalue>* z) {
        while (z != root && z->parent != nullptr && z->parent->color == RED) {

            RBTreeNode<Tkey, Tvalue>* gp = z->parent->parent; //дедушка

            if (gp == nullptr) break;

            if (z->parent == gp->left) {
                RBTreeNode<Tkey, Tvalue>* uncle = gp->right;

                // case 1: дядя существует и он красный — перекраска
                if (uncle != nullptr && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    recalc_height(z->parent);
                    recalc_height(uncle);
                    recalc_height(gp);
                    z = gp;
                }
                else {
                    // case 2: зигзаг (z — правый ребёнок) — сводим к case 3
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);  //малый поворот
                    }

                    // case 3: линия (z — левый ребёнок)
                    z->parent->color = BLACK;
                    gp->color = RED;
                    recalc_height(gp);        // gp стал RED 
                    recalc_height(z->parent); // z->parent стал BLACK 
                    right_rotate(gp); // большой поворот
                }
            }
            else {
                // симметричная логика (отец — правый ребёнок дедушки)
                RBTreeNode<Tkey, Tvalue>* uncle = gp->left;

                // ccase 1: дядя красный — перекраска
                if (uncle != nullptr && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    recalc_height(z->parent);
                    recalc_height(uncle);
                    recalc_height(gp);
                    z = gp;
                }
                else {
                    // case 2: зигзаг (z — левый ребёнок) — сводим к case 3
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }

                    // case 3: линия (z — правый ребёнок)
                    z->parent->color = BLACK;
                    gp->color = RED;
                    recalc_height(gp);        // gp стал RED
                    recalc_height(z->parent); // z->parent стал BLACK
                    left_rotate(gp);
                }
            }
        }

        root->color = BLACK;
        recalc_height(root);
    }
    void printRecursive(RBTreeNode<Tkey, Tvalue>* node, std::string prefix, bool isLeft, bool isRoot) {
        if (node == nullptr) return;

        // сначала правое поддерево
        if (node->right != nullptr) {
            std::string nextPrefix = prefix;
            if (!isRoot) {
                if (isLeft) nextPrefix += "│   ";
                else nextPrefix += "    ";
            }
            printRecursive(node->right, nextPrefix, false, false);
        }

        // печать самого узла
        std::cout << prefix;
        if (!isRoot) {
            if (isLeft) std::cout << "└── ";
            else std::cout << "┌── ";
        }

        std::cout << node->data.first;
        if (node->color == RED) {
            std::cout << "(RED)" << std::endl;
        }
        else {
            std::cout << "(BLACK)" << std::endl;
        }

        //затем левое поддерево
        if (node->left != nullptr) {
            std::string nextPrefix = prefix;
            if (!isRoot) {
                if (isLeft) nextPrefix += "    ";
                else nextPrefix += "│   ";
            }
            printRecursive(node->left, nextPrefix, true, false);
        }
    }

public:
    RBTree() : root(nullptr) {}
    ~RBTree() {
        clear(root);
    }
    void insert(Tkey key, Tvalue value) {
        RBTreeNode<Tkey, Tvalue>* z = new RBTreeNode<Tkey, Tvalue>(key, value);
        RBTreeNode<Tkey, Tvalue>* y = nullptr;
        RBTreeNode<Tkey, Tvalue>* x = root;

        while (x != nullptr) {
            y = x;
            if (key == x->data.first) {
                delete z; 
                return;   
            }
            if (key < x->data.first) x = x->left;
            else x = x->right;
        }

        z->parent = y;
        if (y == nullptr) root = z;
        else if (z->data.first < y->data.first) y->left = z;
        else y->right = z;

        recalc_balance(z);
    }
    void print() {
        if (root == nullptr) {
            std::cout << "Tree is empty" << std::endl;
            return;
        }
        printRecursive(root, "", true, true);
    }
};