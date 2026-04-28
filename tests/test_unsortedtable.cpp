#include <gtest/gtest.h>
#include "../libSortedTableOnVec/sortedTable.h"
#include "../libUnsortedTableOnVec/UnsortedTable.h"
#include "../libSortedTableOnVec/sortedTable.h"
#include "../libITable/itable.h"
#include "../libUnsortedTableOnList/unsortedTableOnList.h"
#include "../libSortedTableOnBST/tabesOnBST.h"
#include <string>
#include <ostream>
#include <algorithm>
#include <random>
#include <vector>

class TreeTableAdvancedTest : public ::testing::Test {
protected:
    TableBST<int, std::string> table;
};

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



TEST_F(TreeTableAdvancedTest, FindReturnsModifiableReference) {
    table.insert(1, "Original");

    std::string& ref = table.find(1);
    ref = "ChangedViaReference";
    EXPECT_EQ(table.find(1), "ChangedViaReference");
}

// --- 2. ТЕСТ ВЫРОЖДЕННОГО ДЕРЕВА ("СОСИСКА") ---
TEST_F(TreeTableAdvancedTest, LongChainSequentialInsert) {
    for (int i = 0; i < 100; ++i) {
        table.insert(i, "val_" + std::to_string(i));
    }

    EXPECT_EQ(table.find(0), "val_0");   
    EXPECT_EQ(table.find(99), "val_99"); 
    EXPECT_TRUE(table.consist(50));
}

// --- 3. ТЕСТ СЛОЖНОГО УДАЛЕНИЯ (Узел с двумя детьми) ---
TEST_F(TreeTableAdvancedTest, RemoveNodeWithTwoChildren) {
    /* Структура:
          50
         /  \
        30   70
       / \   / \
      20  40 60 80
    */
    table.insert(50, "root");
    table.insert(30, "L");
    table.insert(70, "R");
    table.insert(20, "LL");
    table.insert(40, "LR");
    table.insert(60, "RL");
    table.insert(80, "RR");

    table.erase(50);

    EXPECT_FALSE(table.consist(50));
    EXPECT_EQ(table.find(60), "RL");
    EXPECT_EQ(table.find(30), "L"); 
    EXPECT_EQ(table.find(70), "R"); 
}

// --- 4. ТЕСТ НА СТРЕСС И РАНДОМ ---
TEST_F(TreeTableAdvancedTest, StressRandomInsertErase) {
    std::vector<int> keys;
    for (int i = 0; i < 200; ++i) keys.push_back(i);

    auto rd = std::random_device{};
    auto rng = std::default_random_engine{ rd() };
    std::shuffle(keys.begin(), keys.end(), rng);

    for (int k : keys) table.insert(k, "v" + std::to_string(k));

    std::shuffle(keys.begin(), keys.end(), rng);
    for (int i = 0; i < 100; ++i) {
        table.erase(keys[i]);
        EXPECT_FALSE(table.consist(keys[i]));
    }

    for (int i = 100; i < 200; ++i) {
        EXPECT_TRUE(table.consist(keys[i]));
        EXPECT_EQ(table.find(keys[i]), "v" + std::to_string(keys[i]));
    }
}

//  ТЕСТ REPLACE
TEST_F(TreeTableAdvancedTest, ReplaceLogicComprehensive) {

    table.insert(10, "Initial");
    table.replace(10, "Updated");
    EXPECT_EQ(table.find(10), "Updated");
    EXPECT_THROW(table.replace(20, "New"), std::out_of_range);
}

// ТЕСТ ИСКЛЮЧЕНИЙ НА ПУСТОЙ ТАБЛИЦЕ
TEST_F(TreeTableAdvancedTest, EmptyTableExceptions) {
    EXPECT_THROW(table.find(10), std::out_of_range);
    EXPECT_NO_THROW(table.erase(10)); 
    EXPECT_TRUE(table.is_empty());
}

// ТЕСТ ПЕЧАТИ
TEST_F(TreeTableAdvancedTest, SortingIntegrityInPrint) {
    std::vector<int> input = { 40, 10, 50, 20, 30 };
    for (int x : input) table.insert(x, ".");

    std::ostringstream os;
    table.print(os);
    std::string s = os.str();

    size_t p10 = s.find("10");
    size_t p20 = s.find("20");
    size_t p30 = s.find("30");
    size_t p40 = s.find("40");
    size_t p50 = s.find("50");

    EXPECT_TRUE(p10 < p20 && p20 < p30 && p30 < p40 && p40 < p50);
}

