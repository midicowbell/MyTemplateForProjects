#include <gtest/gtest.h>
#include "Tree.h"

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