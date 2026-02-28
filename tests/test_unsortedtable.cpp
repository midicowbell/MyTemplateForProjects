#include <gtest/gtest.h>
#include "UnsortedTable.h"
#include "sortedTable.h"
#include "unsortedTableOnList.h"
#include <string>
#include <ostream>

// Тест 1: Вставка и поиск
TEST(UnsortedTableTest, InsertAndFind) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("apple", 10);
    table.insert("orange", 20);

    EXPECT_EQ(table.find("apple"), 10);
    EXPECT_EQ(table.find("orange"), 20);
    EXPECT_EQ(table.size(), 2);
}

// Тест 2: Проверка на наличие ключа
TEST(UnsortedTableTest, Consist) {
    UnsortedTableOnVec<int, std::string> table;

    table.insert(1, "one");

    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
}

// Тест 3: Замена существующего значения
TEST(UnsortedTableTest, ReplaceExisting) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("power", 9000);
    table.replace("power", 9001);

    EXPECT_EQ(table.find("power"), 9001);
}

// Тест 4: Удаление элемента
TEST(UnsortedTableTest, EraseElement) {
    UnsortedTableOnVec<int, int> table;

    table.insert(10, 100);
    table.insert(20, 200);
    table.erase(10);

    EXPECT_FALSE(table.consist(10));
    EXPECT_TRUE(table.consist(20));
    EXPECT_EQ(table.size(), 1);
}

// Тест 5: Исключение при поиске несуществующего ключа
TEST(UnsortedTableTest, FindNonExistentThrows) {
    UnsortedTableOnVec<int, int> table;

    table.insert(1, 10);

    EXPECT_THROW(table.find(99), std::out_of_range);
}

// Тест 6: Запрет на вставку дубликатов ключей
TEST(UnsortedTableTest, InsertDuplicateThrows) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("unique", 1);

    EXPECT_THROW(table.insert("unique", 2), std::logic_error);
}

TEST(SortedTableOnVecTest, InsertAndFind) {
    SortedTableOnVec<int, std::string> t;
    t.insert(10, "ten");
    t.insert(5, "five");
    t.insert(20, "twenty");

    EXPECT_EQ(t.size(), 3);
    EXPECT_EQ(t.find(10), "ten");
    EXPECT_EQ(t.find(5), "five");
    EXPECT_EQ(t.find(20), "twenty");
}

TEST(SortedTableOnVecTest, InsertDuplicateThrows) {
    SortedTableOnVec<int, std::string> t;
    t.insert(1, "one");
    EXPECT_THROW(t.insert(1, "duplicate"), std::logic_error);
}

TEST(SortedTableOnVecTest, ConsistWorks) {
    SortedTableOnVec<int, std::string> t;
    t.insert(3, "three");

    EXPECT_TRUE(t.consist(3));
    EXPECT_FALSE(t.consist(4));
}

TEST(SortedTableOnVecTest, ReplaceExisting) {
    SortedTableOnVec<int, std::string> t;
    t.insert(7, "seven");
    t.replace(7, "SEVEN");

    EXPECT_EQ(t.find(7), "SEVEN");
}

TEST(SortedTableOnVecTest, ReplaceNonExistingInserts) {
    SortedTableOnVec<int, std::string> t;
    t.replace(100, "hundred");

    EXPECT_TRUE(t.consist(100));
    EXPECT_EQ(t.find(100), "hundred");
}

TEST(SortedTableOnVecTest, EraseExisting) {
    SortedTableOnVec<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");

    t.erase(1);

    EXPECT_FALSE(t.consist(1));
    EXPECT_TRUE(t.consist(2));
    EXPECT_EQ(t.size(), 1);
}

TEST(SortedTableOnVecTest, EraseNonExistingDoesNothing) {
    SortedTableOnVec<int, std::string> t;
    t.insert(1, "one");

    t.erase(999); // не должно упасть

    EXPECT_EQ(t.size(), 1);
    EXPECT_TRUE(t.consist(1));
}

TEST(SortedTableOnVecTest, FindThrowsIfNotFound) {
    SortedTableOnVec<int, std::string> t;
    t.insert(1, "one");

    EXPECT_THROW(t.find(2), std::out_of_range);
}

TEST(SortedTableOnVecTest, IsEmptyWorks) {
    SortedTableOnVec<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());
}

TEST(SortedTableOnVecTest, BinarySearchCorrectPositions) {
    SortedTableOnVec<int, std::string> t;
    t.insert(10, "ten");
    t.insert(20, "twenty");
    t.insert(30, "thirty");

    EXPECT_EQ(t.binary_search(5), 0);
    EXPECT_EQ(t.binary_search(15), 1);
    EXPECT_EQ(t.binary_search(25), 2);
    EXPECT_EQ(t.binary_search(35), 3);
}

// Тест: вставка и поиск
TEST(UnsortedTableOnListTest, InsertAndFind) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(10, "ten");
    t.insert(5, "five");
    t.insert(20, "twenty");

    EXPECT_EQ(t.find(10), "ten");
    EXPECT_EQ(t.find(5), "five");
    EXPECT_EQ(t.find(20), "twenty");
}

// Тест: вставка дубликата
TEST(UnsortedTableOnListTest, InsertDuplicateThrows) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");
    EXPECT_THROW(t.insert(1, "duplicate"), std::logic_error);
}

// Тест: consist
TEST(UnsortedTableOnListTest, ConsistWorks) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(3, "three");

    EXPECT_TRUE(t.consist(3));
    EXPECT_FALSE(t.consist(4));
}

// Тест: replace существующего ключа
TEST(UnsortedTableOnListTest, ReplaceExisting) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(7, "seven");
    t.replace(7, "SEVEN");

    EXPECT_EQ(t.find(7), "SEVEN");
}

// Тест: replace несуществующего ключа → вставка
TEST(UnsortedTableOnListTest, ReplaceNonExistingInserts) {
    UnsortedTableOnList<int, std::string> t;

    t.replace(100, "hundred");

    EXPECT_TRUE(t.consist(100));
    EXPECT_EQ(t.find(100), "hundred");
}

// Тест: find бросает исключение
TEST(UnsortedTableOnListTest, FindThrowsIfNotFound) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");

    EXPECT_THROW(t.find(2), std::logic_error);
}

// Тест: erase существующего ключа
TEST(UnsortedTableOnListTest, EraseExisting) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");
    t.insert(2, "two");

    t.erase(1);

    EXPECT_FALSE(t.consist(1));
    EXPECT_TRUE(t.consist(2));
}

// Тест: erase несуществующего ключа (не должно падать)
TEST(UnsortedTableOnListTest, EraseNonExistingDoesNothing) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");

    t.erase(999); // не должно упасть

    EXPECT_TRUE(t.consist(1));
}

// Тест: is_empty
TEST(UnsortedTableOnListTest, IsEmptyWorks) {
    UnsortedTableOnList<int, std::string> t;

    EXPECT_TRUE(t.is_empty());

    t.insert(1, "one");

    EXPECT_FALSE(t.is_empty());
}

// Тест: print (просто проверяем, что не падает)
TEST(UnsortedTableOnListTest, PrintDoesNotCrash) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");
    t.insert(2, "two");

    std::ostringstream os;
    EXPECT_NO_THROW(t.print(os));
}


