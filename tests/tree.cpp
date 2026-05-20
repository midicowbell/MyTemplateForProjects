#include <gtest/gtest.h>
#include "Tree.h"
#include "../libBSTree/bstree.h"
#include "../libAVLtree/avltree.h"
#include "../libGraph/graph.h"
#include "../libGraph/graph2.h"
#include "../libRBTree/rbtree.h"
class RBTreeTest : public ::testing::Test {
protected:
    RBTree<int, std::string> tree;
};
//БАЗОВЫЕ ОПЕРАЦИИ (ВСТАВКА И ПУСТОТА)
TEST(TreeFullTest, BasicInsertAndEmpty) {
    Tree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
    tree.insert(1, "one");
    EXPECT_FALSE(tree.is_empty());
    tree.insert(1, "second_one");
    ASSERT_NE(tree.find(1), nullptr);
    EXPECT_EQ(*tree.find(1), "one");
}

// FIND

TEST(TreeFullTest, SearchOperations) {
    Tree<int, std::string> tree;
    tree.insert(10, "root");
    tree.insert(5, "left");
    tree.insert(15, "right");
    const std::string* val = tree.find(5);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "left");
    EXPECT_EQ(*tree.find(10), "root");
    EXPECT_EQ(tree.find(999), nullptr);
}

//ВСТАВКА -> УДАЛЕНИЕ -> ВСТАВКА
TEST(TreeFullTest, InsertRemoveInsertCycle) {
    Tree<int, std::string> tree;
    tree.insert(1, "A");
    tree.insert(2, "B");
    tree.insert(3, "C");
    tree.insert(4, "D");
    tree.remove(2);

    EXPECT_EQ(tree.find(2), nullptr);
    EXPECT_NE(tree.find(4), nullptr);
    EXPECT_NE(tree.find(1), nullptr);
    tree.insert(5, "E");
    ASSERT_NE(tree.find(5), nullptr);
    EXPECT_EQ(*tree.find(5), "E");
    EXPECT_NE(tree.find(1), nullptr);
    EXPECT_NE(tree.find(3), nullptr);
    EXPECT_NE(tree.find(4), nullptr);
}

// УДАЛЕНИЕ ДО ПУСТОТЫ
TEST(TreeFullTest, RemoveToEmpty) {
    Tree<int, std::string> tree;

    tree.insert(100, "X");
    tree.insert(200, "Y");
    tree.remove(100);
    tree.remove(200);
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.find(100), nullptr);
    tree.insert(300, "Z");
    EXPECT_FALSE(tree.is_empty());
    EXPECT_EQ(*tree.find(300), "Z");
}

// ТИПЫ ДАННЫХ И ВИЗУАЛЬНЫЕ ОБХОДЫ

TEST(TreeFullTest, TypesAndVisualOutput) {
    Tree<std::string, int> tree;
    tree.insert("Apple", 50);
    tree.insert("Orange", 30);
    tree.insert("Banana", 20);

    EXPECT_EQ(*tree.find("Orange"), 30);
    std::cout << "\n[ИНФО] Визуальная проверка обходов для Apple, Orange, Banana:" << std::endl;
    tree.width();
    tree.lcr();
    tree.clr();
    tree.lrc();

    SUCCEED();
}

// Проверка начального состояния (пустое дерево)
TEST(BSTreeTest, NewTreeIsEmpty) {
    BSTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
}

// Проверка вставки одного элемента
TEST(BSTreeTest, InsertSingleElement) {
    BSTree<int, std::string> tree;
    tree.insert(10, "ten");

    EXPECT_FALSE(tree.is_empty());

    std::string* value = tree.find(10);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "ten");
}

// Поиск несуществующего ключа
TEST(BSTreeTest, FindNonExistentKey) {
    BSTree<int, std::string> tree;
    tree.insert(10, "ten");

    EXPECT_EQ(tree.find(20), nullptr);
}

// Вставка нескольких элементов и сохранение свойств поиска
TEST(BSTreeTest, InsertMultipleElements) {
    BSTree<int, int> tree;
    tree.insert(50, 500);
    tree.insert(30, 300);
    tree.insert(70, 700);
    tree.insert(20, 200);
    tree.insert(40, 400);

    EXPECT_EQ(*tree.find(50), 500);
    EXPECT_EQ(*tree.find(30), 300);
    EXPECT_EQ(*tree.find(70), 700);
    EXPECT_EQ(*tree.find(20), 200);
    EXPECT_EQ(*tree.find(40), 400);
}

// Проверка на отсутствие дубликатов (согласно логике insert из лекций)
TEST(BSTreeTest, InsertDuplicateKeyDoesNothing) {
    BSTree<int, std::string> tree;
    tree.insert(1, "original");
    tree.insert(1, "duplicate");

    std::string* value = tree.find(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "original");
}
// Тест удаления листа
TEST(BSTreeDeleteTest, DeleteLeaf) {
    BSTree<int, std::string> tree;
    tree.insert(10, "root");
    tree.insert(5, "leaf");

    tree.remove(5);
    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_NE(tree.find(10), nullptr);
}

// Тест удаления узла с одним потомком 
TEST(BSTreeDeleteTest, DeleteNodeWithOneChild) {
    BSTree<int, std::string> tree;
    tree.insert(10, "root");
    tree.insert(5, "parent");
    tree.insert(3, "child");

    tree.remove(5);
    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_NE(tree.find(3), nullptr);
}

// Тест удаления узла с двумя потомками
TEST(BSTreeDeleteTest, DeleteNodeWithTwoChildren) {
    BSTree<int, std::string> tree;
    tree.insert(10, "root");
    tree.insert(5, "node_to_delete");
    tree.insert(3, "left");
    tree.insert(7, "right");

    tree.remove(5);
    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_NE(tree.find(3), nullptr);
    EXPECT_NE(tree.find(7), nullptr);
}

// Тест удаления корня
TEST(BSTreeDeleteTest, DeleteRoot) {
    BSTree<int, std::string> tree;
    tree.insert(10, "root");
    tree.insert(15, "right");

    tree.remove(10);
    EXPECT_EQ(tree.find(10), nullptr);
    EXPECT_FALSE(tree.is_empty());
    EXPECT_NE(tree.find(15), nullptr);
}

// Тест удаления несуществующего ключа
TEST(BSTreeDeleteTest, DeleteNonExistentKey) {
    BSTree<int, std::string> tree;
    tree.insert(10, "root");

    tree.remove(99); // Не должно вызывать ошибок
    EXPECT_NE(tree.find(10), nullptr);
}

// БАЗОВЫЕ ОПЕРАЦИИ (ВСТАВКА И ПОИСК)


TEST(AVLTreeTest, InsertAndFind) {
    AVLTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());

    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.insert(5, "five");

    EXPECT_FALSE(tree.is_empty());
    ASSERT_NE(tree.find(10), nullptr);
    EXPECT_EQ(*tree.find(10), "ten");
    EXPECT_EQ(*tree.find(20), "twenty");
    EXPECT_EQ(*tree.find(5), "five");
}

//ПРОВЕРКА БАЛАНСИРОВКИ (ПОВОРОТЫ)


// Случай RR
TEST(AVLTreeTest, RotationRR) {
    AVLTree<int, int> tree;
    tree.insert(10, 10);
    tree.insert(20, 20);
    tree.insert(30, 30);
    /*       (левое вращение)
            10                   20                 
              \                 /   \
                20      ->    10     30
                  \
                   30
    */
    EXPECT_EQ(tree.height(), 2);
}

// Случай LL
TEST(AVLTreeTest, RotationLL) {
    AVLTree<int, int> tree;
    tree.insert(30, 30);
    tree.insert(20, 20);
    tree.insert(10, 10);
    /*     (правое вращение)
               30              20
              /               /  \
             20      ->      10   30
            /
           10
    */
    EXPECT_EQ(tree.height(), 2);
}

// Случай LR
TEST(AVLTreeTest, RotationLR) {
    AVLTree<int, int> tree;
    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.insert(20, 20);
    /*        
              30                    30             20
             /                     /              /  \  
            10              ->    20      ->    10    30
              \                  /
                20              10
    */
    EXPECT_EQ(tree.height(), 2);
    EXPECT_NE(tree.find(20), nullptr);
}

// Случай RL
TEST(AVLTreeTest, RotationRL) {
    AVLTree<int, int> tree;
    tree.insert(10, 10);
    tree.insert(30, 30);
    tree.insert(20, 20);
    /*
        10              10                30
          \               \              /  \
            30 ->          20     ->    10   20
           /                 \
         20                   30
    */
    EXPECT_EQ(tree.height(), 2);
}
TEST(AVLTreeTest, DeleteTriggersDoubleRotation) {
    AVLTree<int, int> tree;

     /*
     *        40  (Баланс: -1)
     *       /  \
     *     20    60 (Баланс: +1)
     *          /
     *        50
     */
    tree.insert(40,40);
    tree.insert(20,20);
    tree.insert(60,60);
    tree.insert(50,50);
    EXPECT_NO_THROW(tree.remove(20));
    /*
     * ШАГ 2: Удаление левого узла (20)
     * Это разрушает баланс корня.
     *
     *        40  (Баланс: -2) <-- КРИТИЧЕСКИЙ УЗЕЛ!
     *          \
     *           60 (Баланс: +1)
     *          /
     *        50
     *
     */

    /*
    * Малый правый поворот вокруг 60
     *        40  
     *          \
     *           50  
     *             \
     *              60
     * 
     * Малый левый поворот вокруг 40
     *         50 
     *        /  \
     *      40    60
     * 
     */
    EXPECT_EQ(tree.find(50) != nullptr, true);
}
// СТРЕСС-ТЕСТ

TEST(AVLTreeTest, SequentialInsertStressTest) {
    AVLTree<int, int> tree;
    int n = 1000;
    for (int i = 1; i <= n; ++i) {
        tree.insert(i, i);
    }

    EXPECT_LE(tree.height(), 15);

    for (int i = 1; i <= n; ++i) {
        ASSERT_NE(tree.find(i), nullptr) << "Key " << i << " not found!";
    }
}

// ТЕСТЫ УДАЛЕНИЯ

TEST(AVLTreeTest, RemoveAndRebalance) {
    AVLTree<int, int> tree;
    tree.insert(20, 20);
    tree.insert(10, 10);
    tree.insert(30, 30);
    tree.insert(5, 5);
    tree.remove(30);

    EXPECT_EQ(tree.find(30), nullptr);
    EXPECT_LE(tree.height(), 2);
    EXPECT_NE(tree.find(20), nullptr);
}
// ТЕСТЫ ДЛЯ МАТРИЦЫ
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

//ТЕСТЫ ДЛЯ СПИСКА
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

// проверка базовой вставки и правила корня
TEST_F(RBTreeTest, RootIsAlwaysBlack) {
    tree.insert(10, "root");
}

// Проверка case 1 
TEST_F(RBTreeTest, Case1Recolor) {
    /*
           20(B)
          /    \
       10(R)  30(R)
     */
    tree.insert(20, "G");                      
    tree.insert(10, "P");                       
    tree.insert(30, "U"); // дядя красный

    // вставка 5 сделает P и U черными, а G красным (и потом G станет черным, так как он корень)
    /*
    * 
                * 20(B)
                 /    \
              10(B)  30(B)
               /
             5(R)
    * 
    * 
    * 
    */
    EXPECT_NO_THROW(tree.insert(5, "Z"));
}

// проверка case 2 и case 3 (Малый и большой повороты)
TEST_F(RBTreeTest, Case2And3Rotations) {
    // создаем линию для case 3
    /*
             30(B)
           /
         20(R)
    */
    tree.insert(30, "G");
    tree.insert(20, "P");
    /*
              30(B)
              /    
             20(R)
            /
            10(R)
    */


    tree.insert(10, "X"); // правый поворот вокруг 30

    /*
            20(B)
             /    \
          10(R)  30(R)
    */






    // создаем "зигзаг" для case 2
    tree.insert(50, "G2");
    tree.insert(40, "P2");
    tree.insert(45, "X2"); // левый поворот вокруг 40 (малый), затем правый вокруг 50 (большой)
    /*
    
    
    50(B)                   50(B)                45(B)
     /                      /                   /     \
  40(R)        ->          45(R)       ->      40(R)    50(R)
                           /         
    \                     40(R)  
    45(R)                   
    */
    EXPECT_NO_THROW();
}

// Массовая вставка и проверка стабильности
TEST_F(RBTreeTest, SequentialInsertion) {
    for (int i = 1; i <= 100; ++i) {
        EXPECT_NO_THROW(tree.insert(i, "val" + std::to_string(i)));
    }
}

TEST(RBTreeVisualTest, PrintWithLines) {
    RBTree<int, int> tree;

    for (int v : {10, 20, 30, 5, 15, 25, 35}) {
        tree.insert(v, v);
    }

    std::cout << "\n[ КРАСНО-ЧЕРНОЕ ДЕРЕВО ]\n" << std::endl;
    tree.print();
    std::cout << "\n[ --------------------- ]" << std::endl;

    SUCCEED();
}