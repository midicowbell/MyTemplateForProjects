#include <gtest/gtest.h>
#include "UnsortedTable.h"
#include "sortedTable.h"
#include "unsortedTableOnList.h"
#include <string>
#include <ostream>
#include "skiplist.h"

//Вставка и поиск
TEST(UnsortedTableTest, InsertAndFind) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("apple", 10);
    table.insert("orange", 20);

    EXPECT_EQ(table.find("apple"), 10);
    EXPECT_EQ(table.find("orange"), 20);
    EXPECT_EQ(table.size(), 2);
}

//Проверка на наличие ключа
TEST(UnsortedTableTest, Consist) {
    UnsortedTableOnVec<int, std::string> table;

    table.insert(1, "one");

    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
}

// Замена существующего значения
TEST(UnsortedTableTest, ReplaceExisting) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("power", 9000);
    table.replace("power", 9001);

    EXPECT_EQ(table.find("power"), 9001);
}

// Удаление элемента
TEST(UnsortedTableTest, EraseElement) {
    UnsortedTableOnVec<int, int> table;

    table.insert(10, 100);
    table.insert(20, 200);
    table.erase(10);

    EXPECT_FALSE(table.consist(10));
    EXPECT_TRUE(table.consist(20));
    EXPECT_EQ(table.size(), 1);
}

// Исключение при поиске несуществующего ключа
TEST(UnsortedTableTest, FindNonExistentThrows) {
    UnsortedTableOnVec<int, int> table;

    table.insert(1, 10);

    EXPECT_THROW(table.find(99), std::out_of_range);
}

// Запрет на вставку дубликатов ключей
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

    t.erase(999);

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

//  вставка и поиск
TEST(UnsortedTableOnListTest, InsertAndFind) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(10, "ten");
    t.insert(5, "five");
    t.insert(20, "twenty");

    EXPECT_EQ(t.find(10), "ten");
    EXPECT_EQ(t.find(5), "five");
    EXPECT_EQ(t.find(20), "twenty");
}

// вставка дубликата
TEST(UnsortedTableOnListTest, InsertDuplicateThrows) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");
    EXPECT_THROW(t.insert(1, "duplicate"), std::logic_error);
}

// consist
TEST(UnsortedTableOnListTest, ConsistWorks) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(3, "three");

    EXPECT_TRUE(t.consist(3));
    EXPECT_FALSE(t.consist(4));
}

//replace существующего ключа
TEST(UnsortedTableOnListTest, ReplaceExisting) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(7, "seven");
    t.replace(7, "SEVEN");

    EXPECT_EQ(t.find(7), "SEVEN");
}

// replace несуществующего ключа → вставка
TEST(UnsortedTableOnListTest, ReplaceNonExistingInserts) {
    UnsortedTableOnList<int, std::string> t;

    t.replace(100, "hundred");

    EXPECT_TRUE(t.consist(100));
    EXPECT_EQ(t.find(100), "hundred");
}

// find бросает исключение
TEST(UnsortedTableOnListTest, FindThrowsIfNotFound) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");

    EXPECT_THROW(t.find(2), std::logic_error);
}

// erase существующего ключа
TEST(UnsortedTableOnListTest, EraseExisting) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");
    t.insert(2, "two");

    t.erase(1);

    EXPECT_FALSE(t.consist(1));
    EXPECT_TRUE(t.consist(2));
}

//erase несуществующего ключа (не должно падать)
TEST(UnsortedTableOnListTest, EraseNonExistingDoesNothing) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");

    t.erase(999); // не должно упасть

    EXPECT_TRUE(t.consist(1));
}

// is_empty
TEST(UnsortedTableOnListTest, IsEmptyWorks) {
    UnsortedTableOnList<int, std::string> t;

    EXPECT_TRUE(t.is_empty());

    t.insert(1, "one");

    EXPECT_FALSE(t.is_empty());
}

//print (просто проверяем, что не падает)
TEST(UnsortedTableOnListTest, PrintDoesNotCrash) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");
    t.insert(2, "two");

    std::ostringstream os;
    EXPECT_NO_THROW(t.print(os));
}
TEST(SkipListTest, InsertAndFind) {
    std::srand(42);
    SkipList<int, int> list(5);

    list.insert(5, 50);
    list.insert(1, 10);
    list.insert(3, 30);

    EXPECT_NE(list.find(1), nullptr);
    EXPECT_NE(list.find(3), nullptr);
    EXPECT_NE(list.find(5), nullptr);
    EXPECT_EQ(list.find(1)->_data.second, 10);
    EXPECT_EQ(list.find(3)->_data.second, 30);
    EXPECT_EQ(list.find(5)->_data.second, 50);
}

TEST(SkipListTest, FindNonExistent) {
    std::srand(42);
    SkipList<int, int> list(5);

    list.insert(1, 10);
    list.insert(3, 30);

    EXPECT_EQ(list.find(2), nullptr);
    EXPECT_EQ(list.find(99), nullptr);
}

TEST(SkipListTest, EmptyList) {
    std::srand(42);
    SkipList<int, int> list(5);

    EXPECT_EQ(list.find(1), nullptr);
}


TEST(SkipListTest, UpdateExistingKey) {
    std::srand(42);
    SkipList<int, int> list(5);

    list.insert(1, 100);
    EXPECT_EQ(list.find(1)->_data.second, 100);

    list.insert(1, 200);
    EXPECT_EQ(list.find(1)->_data.second, 200);
}

TEST(SkipListTest, StringKeys) {
    std::srand(42);
    SkipList<std::string, int> list(5);

    list.insert("apple", 10);
    list.insert("banana", 20);

    EXPECT_EQ(list.find("apple")->_data.second, 10);
    EXPECT_EQ(list.find("banana")->_data.second, 20);
}

TEST(SkipListTest, StringValues) {
    std::srand(42);
    SkipList<int, std::string> list(5);

    list.insert(1, "one");
    list.insert(2, "two");

    EXPECT_EQ(list.find(1)->_data.second, "one");
    EXPECT_EQ(list.find(2)->_data.second, "two");
}

TEST(SkipListTest, NegativeKeys) {
    std::srand(42);
    SkipList<int, int> list(5);

    list.insert(-5, -50);
    list.insert(0, 0);
    list.insert(5, 50);

    EXPECT_EQ(list.find(-5)->_data.second, -50);
    EXPECT_EQ(list.find(0)->_data.second, 0);
    EXPECT_EQ(list.find(5)->_data.second, 50);
}

TEST(SkipListTest, Stress100Elements) {
    std::srand(42);
    SkipList<int, int> list(10);

    for (int i = 0; i < 100; ++i) {
        list.insert(i, i * 10);
    }

    for (int i = 0; i < 100; ++i) {
        EXPECT_NE(list.find(i), nullptr);
        EXPECT_EQ(list.find(i)->_data.second, i * 10);
    }
}

TEST(SkipListTest, DestructorEmpty) {
    SkipList<int, int> list(5);
}

TEST(SkipListTest, DestructorFilled) {
    std::srand(42);
    {
        SkipList<int, int> list(5);
        for (int i = 0; i < 50; ++i) {
            list.insert(i, i);
        }
    }
}

TEST(SkipListTest, PrintDoesNotCrash) {
    std::srand(42);
    SkipList<int, int> list(5);

    list.insert(1, 10);
    list.insert(2, 20);

    EXPECT_NO_THROW(list.print());
}

//  Базовое удаление существующего элемента
TEST(SkipListTest, RemoveExistingElement) {
    std::srand(42);
    SkipList<int, int> list(10);
    list.insert(10, 100);
    list.insert(20, 200);
    list.insert(30, 300);

    list.remove(20);

    EXPECT_EQ(list.find(20), nullptr);
    EXPECT_NE(list.find(10), nullptr);
    EXPECT_NE(list.find(30), nullptr);
}

//Попытка удаления несуществующего элемента
TEST(SkipListTest, RemoveNonExistentElement) {
    std::srand(42);
    SkipList<int, int> list(10);
    list.insert(10, 100);
    list.insert(30, 300);
    list.remove(99);
    EXPECT_NE(list.find(10), nullptr);
    EXPECT_NE(list.find(30), nullptr);
    EXPECT_EQ(list.find(10)->_data.second, 100);
}

//Удаление граничных элементов (первого и последнего)
TEST(SkipListTest, RemoveBoundaryElements) {
    std::srand(42);
    SkipList<int, int> list(10);
    list.insert(5, 50);  
    list.insert(10, 100);
    list.insert(15, 150); 

    list.remove(5);
    EXPECT_EQ(list.find(5), nullptr);
    EXPECT_NE(list.find(10), nullptr);

    list.remove(15);
    EXPECT_EQ(list.find(15), nullptr);
    EXPECT_NE(list.find(10), nullptr);
}

//Смешанные операции (вставка-удаление-вставка)
TEST(SkipListTest, MixedInsertAndRemove) {
    std::srand(42);
    SkipList<int, int> list(10);
    list.insert(10, 100);
    list.insert(20, 200);

    list.remove(10);
    EXPECT_EQ(list.find(10), nullptr);

    list.insert(10, 101); 
    EXPECT_NE(list.find(10), nullptr);
    EXPECT_EQ(list.find(10)->_data.second, 101); 
    EXPECT_NE(list.find(20), nullptr); 
}
