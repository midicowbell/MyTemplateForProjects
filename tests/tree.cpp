#include <gtest/gtest.h>
#include "Tree.h"
#include "../libBSTree/bstree.h"
#include "../libAVLtree/avltree.h"
#include "../libGraph/graph.h"
#include "../libGraph/graph2.h"
#include "../libRBTree/rbtree.h"
#include <string>
#include <vector>
#include <iostream>

class RBTreeTest : public ::testing::Test {
protected:
    RBTree<int, std::string> tree;
};

TEST(TreeFullTest, BasicInsertAndEmpty) {
    Tree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());

    std::vector<std::pair<int, std::string>> data = {
        {50, "root"}, {30, "L"}, {70, "R"}, {20, "LL"}, {40, "LR"}, {60, "RL"}, {80, "RR"}
    };
    for (const auto& p : data) {
        tree.insert(p.first, p.second);
    }

    EXPECT_FALSE(tree.is_empty());

    tree.insert(50, "duplicate_root");
    ASSERT_NE(tree.find(50), nullptr);
    EXPECT_EQ(*tree.find(50), "root");
}

TEST(TreeFullTest, SearchOperations) {
    Tree<int, std::string> tree;
    std::vector<int> keys = { 50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43 };
    for (int k : keys) {
        tree.insert(k, "val_" + std::to_string(k));
    }

    for (int k : keys) {
        const std::string* val = tree.find(k);
        ASSERT_NE(val, nullptr) << "Не найден ключ: " << k;
        EXPECT_EQ(*val, "val_" + std::to_string(k));
    }

    EXPECT_EQ(tree.find(999), nullptr);
    EXPECT_EQ(tree.find(0), nullptr);
    EXPECT_EQ(tree.find(26), nullptr);
}

TEST(TreeFullTest, InsertRemoveInsertCycle) {
    Tree<int, std::string> tree;
    std::vector<int> initial_keys = { 100, 50, 150, 25, 75, 125, 175, 10, 30, 60, 80 };
    for (int k : initial_keys) {
        tree.insert(k, "Data_" + std::to_string(k));
    }

    tree.remove(50); 
    tree.remove(175); 
    tree.remove(10);

    EXPECT_EQ(tree.find(50), nullptr);
    EXPECT_EQ(tree.find(175), nullptr);
    EXPECT_EQ(tree.find(10), nullptr);

    for (int k : {100, 150, 25, 75, 125, 30, 60, 80}) {
        EXPECT_NE(tree.find(k), nullptr) << "Потерян узел после удаления: " << k;
    }
    tree.insert(55, "New_55");
    tree.insert(9, "New_9");
    tree.insert(180, "New_180");

    EXPECT_EQ(*tree.find(55), "New_55");
    EXPECT_EQ(*tree.find(9), "New_9");
    EXPECT_EQ(*tree.find(180), "New_180");
}

TEST(TreeFullTest, RemoveToEmpty) {
    Tree<int, std::string> tree;
    std::vector<int> keys = { 40, 20, 60, 10, 30, 50, 70, 5, 15, 25, 35 };
    for (int k : keys) tree.insert(k, "X");

    for (int k : keys) {
        tree.remove(k);
    }

    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.find(40), nullptr);
    std::vector<int> new_keys = { 500, 250, 750 };
    for (int nk : new_keys) tree.insert(nk, "New");

    EXPECT_FALSE(tree.is_empty());
    EXPECT_EQ(*tree.find(250), "New");
}

TEST(TreeFullTest, TypesAndVisualOutput) {
    Tree<std::string, int> tree;
    std::vector<std::pair<std::string, int>> fruits = {
        {"Watermelon", 10}, {"Banana", 20}, {"Orange", 30}, {"Apple", 50},
        {"Apricot", 15}, {"Mango", 45}, {"Cherry", 25}, {"Lemon", 35}
    };
    for (const auto& f : fruits) {
        tree.insert(f.first, f.second);
    }

    EXPECT_EQ(*tree.find("Orange"), 30);
    EXPECT_EQ(*tree.find("Apricot"), 15);

    std::cout << "\n[ИНФО] Визуальная проверка обходов крупного строкового дерева:" << std::endl;
    tree.width();
    tree.lcr();
    tree.clr();
    tree.lrc();

    SUCCEED();
}

TEST(BSTreeTest, NewTreeIsEmpty) {
    BSTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(BSTreeTest, InsertSingleElement) {
    BSTree<int, std::string> tree;
    tree.insert(10, "ten");
    EXPECT_FALSE(tree.is_empty());
    std::string* value = tree.find(10);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "ten");
}

TEST(BSTreeTest, FindNonExistentKey) {
    BSTree<int, std::string> tree;
    tree.insert(50, "root");
    tree.insert(25, "left");
    tree.insert(75, "right");
    EXPECT_EQ(tree.find(100), nullptr);
}

TEST(BSTreeTest, InsertMultipleElements) {
    BSTree<int, int> tree;
    std::vector<int> keys = { 80, 40, 120, 20, 60, 100, 140, 10, 30, 50, 70, 90, 110, 130, 150 };
    for (int k : keys) {
        tree.insert(k, k * 10);
    }

    for (int k : keys) {
        ASSERT_NE(tree.find(k), nullptr) << "Потерялся ключ: " << k;
        EXPECT_EQ(*tree.find(k), k * 10);
    }
}

TEST(BSTreeTest, InsertDuplicateKeyDoesNothing) {
    BSTree<int, std::string> tree;
    std::vector<int> keys = { 50, 30, 70, 20, 40 };
    for (int k : keys) tree.insert(k, "initial_" + std::to_string(k));

    tree.insert(50, "duplicate_50");
    tree.insert(20, "duplicate_20");

    EXPECT_EQ(*tree.find(50), "initial_50");
    EXPECT_EQ(*tree.find(20), "initial_20");
}

TEST(BSTreeDeleteTest, DeleteLeaf) {
    BSTree<int, std::string> tree;
    std::vector<int> keys = { 60, 30, 90, 15, 45, 75, 105, 5, 20, 40, 50 };
    for (int k : keys) tree.insert(k, "val");
    tree.remove(50);
    EXPECT_EQ(tree.find(50), nullptr);
    EXPECT_NE(tree.find(45), nullptr);
    EXPECT_NE(tree.find(40), nullptr);
}

TEST(BSTreeDeleteTest, DeleteNodeWithOneChild) {
    BSTree<int, std::string> tree;
    std::vector<int> keys = { 100, 50, 150, 25, 75, 12, 35 };
    for (int k : {100, 50, 150, 25, 75, 85, 95}) tree.insert(k, "OK");
    tree.remove(75);
    EXPECT_EQ(tree.find(75), nullptr);
    EXPECT_NE(tree.find(85), nullptr);
    EXPECT_NE(tree.find(95), nullptr);
    EXPECT_NE(tree.find(50), nullptr);
}

TEST(BSTreeDeleteTest, DeleteNodeWithTwoChildren) {
    BSTree<int, std::string> tree;
    std::vector<int> keys = { 100, 60, 150, 40, 80, 130, 180, 20, 50, 70, 90, 110, 140, 170, 190 };
    for (int k : keys) tree.insert(k, "data_" + std::to_string(k));
    tree.remove(60);

    EXPECT_EQ(tree.find(60), nullptr);
    for (int k : {40, 80, 20, 50, 70, 90, 100, 150}) {
        EXPECT_NE(tree.find(k), nullptr) << "Связи разорваны для ключа: " << k;
    }
}

TEST(BSTreeDeleteTest, DeleteRoot) {
    BSTree<int, std::string> tree;
    std::vector<int> keys = { 50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 55, 68, 82, 93 };
    for (int k : keys) tree.insert(k, "X");

    tree.remove(50);

    EXPECT_EQ(tree.find(50), nullptr);
    EXPECT_FALSE(tree.is_empty());

    for (int k : {25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 55, 68, 82, 93}) {
        EXPECT_NE(tree.find(k), nullptr) << "Корень утянул за собой узел: " << k;
    }
}

TEST(BSTreeDeleteTest, DeleteNonExistentKey) {
    BSTree<int, std::string> tree;
    std::vector<int> keys = { 40, 20, 60, 10, 30, 50, 70 };
    for (int k : keys) tree.insert(k, "val");

    EXPECT_NO_THROW(tree.remove(999));
    EXPECT_NO_THROW(tree.remove(-50));

    for (int k : keys) {
        EXPECT_NE(tree.find(k), nullptr);
    }
}


TEST(AVLTreeTest, InsertAndFind) {
    AVLTree<int, std::string> tree;
    std::vector<int> keys = { 100, 50, 150, 25, 75, 125, 175, 10, 35, 60, 90 };
    for (int k : keys) tree.insert(k, "avl_" + std::to_string(k));

    for (int k : keys) {
        ASSERT_NE(tree.find(k), nullptr);
        EXPECT_EQ(*tree.find(k), "avl_" + std::to_string(k));
    }
}

TEST(AVLTreeTest, RotationRR) {
    AVLTree<int, int> tree;
    std::vector<int> base = { 50, 25, 75, 12, 37, 60 };
    for (int k : base) tree.insert(k, k);
    tree.insert(80, 80);
    tree.insert(90, 90);

    EXPECT_LE(tree.height(), 4);
    EXPECT_NE(tree.find(80), nullptr);
    EXPECT_NE(tree.find(75), nullptr);
    EXPECT_NE(tree.find(90), nullptr);
}

TEST(AVLTreeTest, RotationLL) {
    AVLTree<int, int> tree;
    std::vector<int> base = { 50, 30, 70, 80, 90 };
    for (int k : base) tree.insert(k, k);

    tree.insert(20, 20);
    tree.insert(10, 10);

    EXPECT_LE(tree.height(), 4);
    for (int k : {50, 30, 70, 80, 90, 20, 10}) {
        EXPECT_NE(tree.find(k), nullptr);
    }
}

TEST(AVLTreeTest, RotationLR) {
    AVLTree<int, int> tree;
    std::vector<int> base = { 100, 50, 150, 125, 175, 25 };
    for (int k : base) tree.insert(k, k);

    tree.insert(40, 40);
    tree.insert(35, 35); 

    EXPECT_LE(tree.height(), 4);
    EXPECT_NE(tree.find(35), nullptr);
    EXPECT_NE(tree.find(40), nullptr);
}

TEST(AVLTreeTest, RotationRL) {
    AVLTree<int, int> tree;
    std::vector<int> base = { 50, 25, 100, 12, 37, 75 };
    for (int k : base) tree.insert(k, k);

    tree.insert(85, 85);
    tree.insert(80, 80);

    EXPECT_LE(tree.height(), 4);
    EXPECT_NE(tree.find(80), nullptr);
    EXPECT_NE(tree.find(85), nullptr);
}

TEST(AVLTreeTest, DeleteTriggersDoubleRotation) {
    AVLTree<int, int> tree;
    std::vector<int> keys = { 100, 50, 150, 25, 75, 125, 175, 10, 60, 90, 110 };
    for (int k : keys) tree.insert(k, k);

    EXPECT_NO_THROW(tree.remove(175));

    EXPECT_EQ(tree.find(175), nullptr);
    EXPECT_LE(tree.height(), 4); 
    EXPECT_NE(tree.find(100), nullptr);
    EXPECT_NE(tree.find(125), nullptr);
}

TEST(AVLTreeTest, SequentialInsertStressTest) {
    AVLTree<int, int> tree;
    int n = 1500; 
    for (int i = 1; i <= n; ++i) {
        tree.insert(i, i);
    }

    EXPECT_LE(tree.height(), 15);

    for (int i = 1; i <= n; ++i) {
        ASSERT_NE(tree.find(i), nullptr) << "Ключ " << i << " потерялся во время массовой балансировки!";
    }
}

TEST(AVLTreeTest, RemoveAndRebalance) {
    AVLTree<int, int> tree;
    std::vector<int> keys = { 44, 17, 78, 32, 50, 88, 48, 62, 54, 10, 22, 15, 20, 25, 80 };
    for (int k : keys) tree.insert(k, k);

    tree.remove(32);
    tree.remove(44); 
    tree.remove(10);

    EXPECT_EQ(tree.find(32), nullptr);
    EXPECT_EQ(tree.find(44), nullptr);
    EXPECT_EQ(tree.find(10), nullptr);

    EXPECT_LE(tree.height(), 5); 
}

TEST(MatrixGraphTest, AddAndRemoveEdges) {
    AdjMatirxGraph g(4, false, true);
    EXPECT_NO_THROW(g.addEdge(0, 1, 10));
    EXPECT_NO_THROW(g.addEdge(1, 2, 20));
    EXPECT_NO_THROW(g.addEdge(2, 3, 30));
    EXPECT_NO_THROW(g.removeEdge(0, 1));
    EXPECT_NO_THROW(g.removeEdge(0, 3));
}

TEST(MatrixGraphTest, AddEdgesAndRemoveVertex) {
    AdjMatirxGraph g(3, false, false);
    EXPECT_NO_THROW(g.addEdge(1, 0, 1));
    EXPECT_NO_THROW(g.addEdge(1, 2, 1));
    EXPECT_NO_THROW(g.removeVertex(1));
    EXPECT_NO_THROW(g.removeVertex(1));
}

TEST(MatrixGraphTest, InvalidIndicesProtection) {
    AdjMatirxGraph g(3, false, false);
    EXPECT_NO_THROW(g.addEdge(0, 5, 10));
    EXPECT_NO_THROW(g.removeEdge(1, -1));
    EXPECT_NO_THROW(g.removeVertex(10));
}

TEST(ListGraphTest, ConstructorInsertAndEdgeDelete) {
    std::vector<EdgeInput<int>> initial_edges = { {0, 1}, {1, 2} };
    AdjListGraph<int> g(4, false, false, initial_edges);
    EXPECT_NO_THROW(g.add_edge(2, 3, 1));
    EXPECT_NO_THROW(g.delete_edge(0, 1));
    EXPECT_NO_THROW(g.delete_edge(2, 3));
}

TEST(ListGraphTest, AddEdgesAndPhysicalVertexDelete) {
    std::vector<EdgeInput<int>> empty_data;
    AdjListGraph<int> g(5, false, false, empty_data);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 2, 1);
    g.add_edge(2, 3, 1);
    g.add_edge(3, 4, 1);
    EXPECT_NO_THROW(g.delete_vertex(2));
    EXPECT_NO_THROW(g.delete_vertex(10));
}

TEST(ListGraphTest, InsertAndRunDijkstra) {
    std::vector<EdgeInput<int>> empty_data;
    AdjListGraph<int> g(4, false, true, empty_data);
    g.add_edge(0, 1, 5);
    g.add_edge(1, 2, 3);
    g.add_edge(0, 2, 10);
    g.add_edge(2, 3, 2);
    EXPECT_NO_THROW(g.djikrstra(0, 3));
    EXPECT_NO_THROW(g.djikrstra(0, 99));
}

TEST(ListGraphTest, DijkstraExecution) {
    std::vector<EdgeInput<int>> data = { {0, 1, 5}, {1, 2, 10} };
    AdjListGraph<int> g(3, false, true, data);
    EXPECT_NO_THROW(g.djikrstra(0, 2));
}

TEST(ListGraphTest, VertexDeletionIntegrity) {
    std::vector<EdgeInput<int>> data = { {0, 1}, {1, 2}, {2, 0} };
    AdjListGraph<int> g(3, true, false, data);
    EXPECT_NO_THROW(g.delete_vertex(1));
}

TEST_F(RBTreeTest, RootIsAlwaysBlack) {
    tree.insert(100, "root");
    tree.insert(50, "L");
    tree.insert(150, "R");
    tree.insert(200, "RR");
    SUCCEED();
}

TEST_F(RBTreeTest, Case1Recolor) {
    std::vector<int> base = { 100, 50, 150, 25, 75, 125, 175 };
    for (int k : base) tree.insert(k, "base");

    tree.insert(12, "node1");
    tree.insert(35, "node2");

    EXPECT_NO_THROW(tree.insert(6, "trigger_recolor"));
}

TEST_F(RBTreeTest, Case2And3Rotations) {
    std::vector<int> base = { 200, 100, 300, 50, 150, 250, 350, 25, 75 };
    for (int k : base) tree.insert(k, "V");
    EXPECT_NO_THROW({
        tree.insert(12, "zig");
        tree.insert(18, "zag");
        });
    EXPECT_NO_THROW({
        tree.insert(5, "line1");
        tree.insert(2, "line2");
        });
}

TEST_F(RBTreeTest, SequentialInsertion) {
    for (int i = 1; i <= 250; ++i) {
        EXPECT_NO_THROW(tree.insert(i, "value_" + std::to_string(i)));
    }
}

TEST(RBTreeVisualTest, PrintWithLines) {
    RBTree<int, int> tree;
    std::vector<int> visual_keys = { 100, 50, 150, 25, 75, 125, 175, 12, 37, 62, 87, 112, 137, 162, 190 };
    for (int v : visual_keys) {
        tree.insert(v, v);
    }

    std::cout << "\n[ КРАСНО-ЧЕРНОЕ ДЕРЕВО (БОЛЬШОЕ ЗАПОЛНЕНИЕ) ]\n" << std::endl;
    tree.print();
    std::cout << "\n[ ----------------------------------------- ]" << std::endl;

    SUCCEED();
}

TEST(AVLTreeTest, NotebookCascadeDeleteLeaf25) {
    AVLTree<int, int> tree;

    // правя ветка
    tree.insert(40, 40);
    tree.insert(60, 60);
    tree.insert(50, 50);
    tree.insert(70, 70);
    tree.insert(45, 45);
    tree.insert(55, 55);
    tree.insert(65, 65);
    tree.insert(80, 80);
    tree.insert(75, 75); 

    // левая ветка
    tree.insert(20, 20);
    tree.insert(15, 15);
    tree.insert(25, 25); 
    tree.insert(5, 5);   

    ASSERT_NE(tree.find(25), nullptr);

    EXPECT_NO_THROW(tree.remove(25));

    EXPECT_EQ(tree.find(25), nullptr);

    // Проверяем, что каскад из двух поворотов не порвал связи у остальных узлов
    std::vector<int> expected_keys = { 40, 20, 60, 15, 5, 50, 70, 45, 55, 65, 80, 75 };
    for (int k : expected_keys) {
        EXPECT_NE(tree.find(k), nullptr) << "Каскадная балансировка после удаления 25 потеряла узел: " << k;
    }

    EXPECT_LE(tree.height(), 4);
/*
                      ( 40 ) [+1]
                     /          \
           ( 20 ) [-1]          ( 60 ) [+1]
          /          \          /          \
     ( 15 )          ( 25 )   ( 50 )        ( 70 )
    /                         /   \         /   \
 ( 5 )                    ( 45 ) ( 55 )  ( 65 ) ( 80 )
                                                /
                                             ( 75 )
*/
 /*
                       ( 40 ) [+1]
                      /          \
           *( 20 ) [-2]          ( 60 ) [+1]
           /          \          /          \
      ( 15 )          [  ]     ( 50 )        ( 70 )
     /                         /   \         /   \
  ( 5 )                    ( 45 ) ( 55 )  ( 65 ) ( 80 )
                                                 /
                                              ( 75 )
 */

 //
 // Правый поворот вокруг 20
 //
 /*
 
                      *( 40 ) [+2]  
                      /          \
                  ( 15 )          ( 60 ) [+1]
                /      \          /          \
           ( 5 )        ( 20 )  ( 50 )        ( 70 )
                               /   \         /   \
                           ( 45 ) ( 55 )  ( 65 ) ( 80 )
                                                 /
                                              ( 75 )
 */

 // финальный левый поворот вокруг 40
 /*
                       ( 60 ) [0]
                      /          \
            ( 40 ) [0]            ( 70 ) [0]
           /          \          /      \
      ( 15 )          ( 50 )  ( 65 )    ( 80 )
     /      \        /      \           /
  ( 5 )      ( 20 ) ( 45 )  ( 55 )   ( 75 )
 */
}
TEST(AVLTreeTest, NotebookInsertThreeDeepRotation) {
    AVLTree<int, int> tree;
    // правая сторона
    tree.insert(60, 60);
    tree.insert(80, 80);
    tree.insert(70, 70);
    tree.insert(90, 90);

    // левая сторона 
    tree.insert(30, 30);
    tree.insert(50, 50);
    tree.insert(40, 40);
    tree.insert(55, 55);
    tree.insert(10, 10);
    tree.insert(20, 20);
    tree.insert(5, 5);

    EXPECT_NO_THROW(tree.insert(3, 3));

    ASSERT_NE(tree.find(3), nullptr);
    EXPECT_EQ(*tree.find(3), 3);

    for (int k : {5, 10, 20, 30, 60}) {
        EXPECT_NE(tree.find(k), nullptr) << "Поворот из-за тройки снес узел: " << k;
    }

    EXPECT_LE(tree.height(), 4);
        // исходное дерево до вставки, высота - 4
        /*
                                            ( 60 ) [-1]
                                           /          \
                                 ( 30 ) [0]            ( 80 ) [0]
                                /          \          /          \
                           ( 10 ) [0]      ( 50 )  ( 70 )        ( 90 )
                          /        \       /      \
                       ( 5 )      ( 20 ) ( 40 )    ( 55 )
        */
        // вставка узла 3.
        /*
                                          *( 60 ) [-2] 
                                           /          \
                                 ( 30 ) [-1]           ( 80 ) [0]
                                /          \          /          \
                           ( 10 ) [-1]     ( 50 )  ( 70 )        ( 90 )
                          /        \       /      \
                       ( 5 ) [-1] ( 20 ) ( 40 )    ( 55 )
                      /
                   +( 3 )
        */

        // результат правого поворота вокруг корня 60
        /*
         * узел 60 ушел в -2, а его левый ребенок 30 находится в -1, следовательно LL
         * делаем одинарный правый поворот вокруг 60
                                            ( 30 ) [0] 
                                           /          \
                                 ( 10 ) [-1]           ( 60 ) [0]
                                /        \            /          \
                             ( 5 ) [-1]  ( 20 )    ( 50 )        ( 80 )
                            /                      /    \        /    \
                         ( 3 )                  ( 40 )  ( 55 ) ( 70 ) ( 90 )
        */
}
TEST_F(RBTreeTest, PerfectTreeCascadeRecolorToRotation) {
    std::vector<int> base = { 100, 50, 150, 25, 75, 125, 175, 12, 37, 110, 140, 6, 18 };
    for (int k : base) {
        tree.insert(k, "DATA");
    }

    ASSERT_NE(tree.find(25), nullptr);
    ASSERT_NE(tree.find(50), nullptr);
    ASSERT_NE(tree.find(6), nullptr);
    ASSERT_NE(tree.find(18), nullptr);
    ASSERT_NE(tree.find(12), nullptr);

    EXPECT_EQ(tree.find(25)->color, RED);
    EXPECT_EQ(tree.find(50)->color, BLACK);
    EXPECT_EQ(tree.find(12)->color, BLACK);
    EXPECT_EQ(tree.find(6)->color, RED);
    EXPECT_EQ(tree.find(18)->color, RED);

    EXPECT_NO_THROW({
        tree.insert(3, "BOMB");
        });
    ASSERT_NE(tree.find(25), nullptr);
    ASSERT_NE(tree.find(50), nullptr);
    ASSERT_NE(tree.find(12), nullptr);
    ASSERT_NE(tree.find(6), nullptr);
    ASSERT_NE(tree.find(18), nullptr);
    ASSERT_NE(tree.find(3), nullptr);

    EXPECT_EQ(tree.find(25)->color, BLACK);
    EXPECT_EQ(tree.find(50)->color, RED);
    EXPECT_EQ(tree.find(12)->color, RED);
    EXPECT_EQ(tree.find(6)->color, BLACK);
    EXPECT_EQ(tree.find(18)->color, BLACK);
    EXPECT_EQ(tree.find(3)->color, RED);

    if (tree.find(50)->left != nullptr) {
        EXPECT_EQ(tree.find(50)->left->data.first, 37);
    }
    else {
        FAIL();
    }

    if (tree.find(6)->left != nullptr) {
        EXPECT_EQ(tree.find(6)->left->data.first, 3);
    }
    else {
        FAIL();
    }
}