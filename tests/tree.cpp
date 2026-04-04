#include <gtest/gtest.h>
#include "Tree.h"
#include "../libBSTree/bstree.h"
// ==============================================================
// 1. БАЗОВЫЕ ОПЕРАЦИИ (ВСТАВКА И ПУСТОТА)
// ==============================================================
TEST(TreeFullTest, BasicInsertAndEmpty) {
    Tree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
    tree.insert(1, "one");
    EXPECT_FALSE(tree.is_empty());
    tree.insert(1, "second_one");
    ASSERT_NE(tree.find(1), nullptr);
    EXPECT_EQ(*tree.find(1), "one");
}

// ==============================================================
// 2. ПОИСК (FIND)
// ==============================================================
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

// ==============================================================
// 3. ЦИКЛ: ВСТАВКА -> УДАЛЕНИЕ -> ВСТАВКА
// ==============================================================
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

// ==============================================================
// 4. УДАЛЕНИЕ ДО ПУСТОТЫ
// ==============================================================
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

// ==============================================================
// 5. ТИПЫ ДАННЫХ И ВИЗУАЛЬНЫЕ ОБХОДЫ
// ==============================================================
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

// Тест 1: Проверка начального состояния (пустое дерево)
TEST(BSTreeTest, NewTreeIsEmpty) {
    BSTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
}

// Тест 2: Проверка вставки одного элемента
TEST(BSTreeTest, InsertSingleElement) {
    BSTree<int, std::string> tree;
    tree.insert(10, "ten");

    EXPECT_FALSE(tree.is_empty());

    std::string* value = tree.find(10);
    ASSERT_NE(value, nullptr); // Указатель не должен быть нулевым
    EXPECT_EQ(*value, "ten");
}

// Тест 3: Поиск несуществующего ключа
TEST(BSTreeTest, FindNonExistentKey) {
    BSTree<int, std::string> tree;
    tree.insert(10, "ten");

    EXPECT_EQ(tree.find(20), nullptr); // Должен вернуть nullptr
}

// Тест 4: Вставка нескольких элементов и сохранение свойств поиска
TEST(BSTreeTest, InsertMultipleElements) {
    BSTree<int, int> tree;
    tree.insert(50, 500);
    tree.insert(30, 300);
    tree.insert(70, 700);
    tree.insert(20, 200);
    tree.insert(40, 400);

    // Проверяем наличие всех ключей
    EXPECT_EQ(*tree.find(50), 500);
    EXPECT_EQ(*tree.find(30), 300);
    EXPECT_EQ(*tree.find(70), 700);
    EXPECT_EQ(*tree.find(20), 200);
    EXPECT_EQ(*tree.find(40), 400);
}

// Тест 5: Проверка на отсутствие дубликатов (согласно логике insert из лекций)
TEST(BSTreeTest, InsertDuplicateKeyDoesNothing) {
    BSTree<int, std::string> tree;
    tree.insert(1, "original");
    tree.insert(1, "duplicate"); // Вторая вставка не должна сработать

    std::string* value = tree.find(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "original"); // Значение не должно измениться
}
// Тест удаления листа [1]
TEST(BSTreeDeleteTest, DeleteLeaf) {
    BSTree<int, std::string> tree;
    tree.insert(10, "root");
    tree.insert(5, "leaf");

    tree.remove(5);
    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_NE(tree.find(10), nullptr);
}

// Тест удаления узла с одним потомком [2]
TEST(BSTreeDeleteTest, DeleteNodeWithOneChild) {
    BSTree<int, std::string> tree;
    tree.insert(10, "root");
    tree.insert(5, "parent");
    tree.insert(3, "child"); // Узел 5 имеет одного потомка 3

    tree.remove(5);
    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_NE(tree.find(3), nullptr); // 3 должен "подтянуться" на место 5
}

// Тест удаления узла с двумя потомками [2]
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