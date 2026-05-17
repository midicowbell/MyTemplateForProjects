#include <gtest/gtest.h>
#include "../libSortedTableOnVec/sortedTable.h"
#include "../libUnsortedTableOnVec/UnsortedTable.h"
#include "../libSortedTableOnVec/sortedTable.h"
#include "../libITable/itable.h"
#include "../libUnsortedTableOnList/unsortedTableOnList.h"
#include "../libSortedTableOnBST/tabesOnBST.h"
#include "../libSortedTableOnAVL/tableAVL.h"
#include "../libHashTable/hashTable2.h"
#include "../libHashTable/hashTable3.h"
#include <string>
#include <ostream>
#include <algorithm>
#include <random>
#include <vector>

class TreeTableAdvancedTest : public ::testing::Test {
protected:
    TableBST<int, std::string> table;
};
class TableAVLAdvancedTest : public ::testing::Test {
protected:
    TableAVL<int, std::string> table;
};

// Вставка и поиск
TEST(UnsortedTableTest, InsertAndFind) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("apple", 10);
    table.insert("orange", 20);

    EXPECT_EQ(table.find("apple"), 10);
    EXPECT_EQ(table.find("orange"), 20);
    EXPECT_EQ(table.size(), 2);
}

// Проверка на наличие ключа
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

//удаление элемента
TEST(UnsortedTableTest, EraseElement) {
    UnsortedTableOnVec<int, int> table;

    table.insert(10, 100);
    table.insert(20, 200);
    table.erase(10);

    EXPECT_FALSE(table.consist(10));
    EXPECT_TRUE(table.consist(20));
    EXPECT_EQ(table.size(), 1);
}

//  Исключение при поиске несуществующего ключа
TEST(UnsortedTableTest, FindNonExistentThrows) {
    UnsortedTableOnVec<int, int> table;

    table.insert(1, 10);

    EXPECT_THROW(table.find(99), std::out_of_range);
}

//  Запрет на вставку дубликатов ключей
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

// вставка и поиск
TEST(UnsortedTableOnListTest, InsertAndFind) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(10, "ten");
    t.insert(5, "five");
    t.insert(20, "twenty");

    EXPECT_EQ(t.find(10), "ten");
    EXPECT_EQ(t.find(5), "five");
    EXPECT_EQ(t.find(20), "twenty");
}

//  вставка дубликата
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

// replace существующего ключа
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

//  erase существующего ключа
TEST(UnsortedTableOnListTest, EraseExisting) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");
    t.insert(2, "two");

    t.erase(1);

    EXPECT_FALSE(t.consist(1));
    EXPECT_TRUE(t.consist(2));
}

//  erase несуществующего ключа
TEST(UnsortedTableOnListTest, EraseNonExistingDoesNothing) {
    UnsortedTableOnList<int, std::string> t;

    t.insert(1, "one");

    t.erase(999); 

    EXPECT_TRUE(t.consist(1));
}

//  is_empty
TEST(UnsortedTableOnListTest, IsEmptyWorks) {
    UnsortedTableOnList<int, std::string> t;

    EXPECT_TRUE(t.is_empty());

    t.insert(1, "one");

    EXPECT_FALSE(t.is_empty());
}

// print (просто проверяем, что не падает)
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

// ТЕСТ ВЫРОЖДЕННОГО ДЕРЕВА
TEST_F(TreeTableAdvancedTest, LongChainSequentialInsert) {
    for (int i = 0; i < 100; ++i) {
        table.insert(i, "val_" + std::to_string(i));
    }

    EXPECT_EQ(table.find(0), "val_0");   
    EXPECT_EQ(table.find(99), "val_99"); 
    EXPECT_TRUE(table.consist(50));
}

//ТЕСТ СЛОЖНОГО УДАЛЕНИЯ
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

// ТЕСТ НА СТРЕСС И РАНДОМ
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



// ТЕСТЫ БАЛАНСИРОВКИ (ПОВОРОТЫ)

TEST_F(TableAVLAdvancedTest, RotationLL) {
    table.insert(30, "A");
    table.insert(20, "B");
    table.insert(10, "C"); 

    EXPECT_TRUE(table.consist(10));
    EXPECT_TRUE(table.consist(20));
    EXPECT_TRUE(table.consist(30));
    EXPECT_EQ(table.find(20), "B");
}

TEST_F(TableAVLAdvancedTest, RotationRR) {
    table.insert(10, "A");
    table.insert(20, "B");
    table.insert(30, "C"); 

    EXPECT_TRUE(table.consist(10));
    EXPECT_TRUE(table.consist(20));
    EXPECT_TRUE(table.consist(30));
}

TEST_F(TableAVLAdvancedTest, RotationLR) {
    table.insert(30, "A");
    table.insert(10, "B");
    table.insert(20, "C");

    EXPECT_TRUE(table.consist(10));
    EXPECT_TRUE(table.consist(20));
    EXPECT_TRUE(table.consist(30));
}

TEST_F(TableAVLAdvancedTest, RotationRL) {
    table.insert(10, "A");
    table.insert(30, "B");
    table.insert(20, "C");

    EXPECT_TRUE(table.consist(10));
    EXPECT_TRUE(table.consist(20));
    EXPECT_TRUE(table.consist(30));
}

// УДАЛЕНИЕ С КАСКАДНОЙ БАЛАНСИРОВКОЙ
TEST_F(TableAVLAdvancedTest, EraseWithCascadingBalance) {
  
    std::vector<int> keys = { 50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35 };
    for (int k : keys) {
        table.insert(k, std::to_string(k));
    }
    table.erase(80);
    table.erase(75);
    table.erase(60);
    std::vector<int> remaining = { 50, 25, 10, 30, 5, 15, 27, 35 };
    for (int k : remaining) {
        EXPECT_TRUE(table.consist(k)) << "Key " << k << " is missing after cascading delete!";
    }
}

// СТРЕСС-ТЕСТ: ПОСЛЕДОВАТЕЛЬНАЯ ВСТАВКА
TEST_F(TableAVLAdvancedTest, MassiveSequentialInsertAndErase) {
    const int N = 10000;
    for (int i = 0; i < N; ++i) {
        table.insert(i, "val");
    }

    EXPECT_EQ(table.find(0), "val");
    EXPECT_EQ(table.find(N - 1), "val");
    EXPECT_EQ(table.find(N / 2), "val");

    for (int i = 0; i < N; i += 2) {
        table.erase(i);
    }

    EXPECT_FALSE(table.consist(0));
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(N - 2));
    EXPECT_TRUE(table.consist(N - 1));
}

//СТРЕСС-ТЕСТ С РАНДОМОМ
TEST_F(TableAVLAdvancedTest, StressRandomInsertErase) {
    std::vector<int> keys;
    const int SIZE = 1000;
    for (int i = 0; i < SIZE; ++i) keys.push_back(i);

    auto rd = std::random_device{};
    auto rng = std::default_random_engine{ rd() };

    std::shuffle(keys.begin(), keys.end(), rng);
    for (int k : keys) {
        table.insert(k, "v" + std::to_string(k));
    }

    std::shuffle(keys.begin(), keys.end(), rng);
    for (int i = 0; i < SIZE / 2; ++i) {
        table.erase(keys[i]);
        EXPECT_FALSE(table.consist(keys[i]));
    }
    for (int i = SIZE / 2; i < SIZE; ++i) {
        EXPECT_TRUE(table.consist(keys[i]));
        EXPECT_EQ(table.find(keys[i]), "v" + std::to_string(keys[i]));
    }
}

//ТЕСТ ИСКЛЮЧЕНИЙ И REPLACE
TEST_F(TableAVLAdvancedTest, ReplaceAndExceptionsLogic) {
    table.insert(10, "Initial");
    table.replace(10, "Updated");
    EXPECT_EQ(table.find(10), "Updated");

    EXPECT_THROW(table.replace(20, "New"), std::invalid_argument);
    EXPECT_THROW(table.find(999), std::invalid_argument);

    EXPECT_NO_THROW(table.erase(999)); 
}

// ПЕЧАТЬ
TEST_F(TableAVLAdvancedTest, SortingIntegrityInPrint) {
    std::vector<int> input = { 50, 40, 30, 20, 10 };
    for (int x : input) table.insert(x, ".");

    std::ostringstream os;
    table.print(os);
    std::string s = os.str();

    size_t p10 = s.find("10");
    size_t p20 = s.find("20");
    size_t p30 = s.find("30");
    size_t p40 = s.find("40");
    size_t p50 = s.find("50");

    EXPECT_TRUE(p10 != std::string::npos); 
    EXPECT_TRUE(p10 < p20 && p20 < p30 && p30 < p40 && p40 < p50);
}



// Тест на переполнение
TEST(DoubleHashingHardcore, OverflowProtection) {
    HashTableDoubleHashing<int> table(3);

    table.insert("A", 1);
    table.insert("B", 2);
    table.insert("C", 3);

    EXPECT_THROW(table.insert("D", 4), std::overflow_error);
}

// Тест на переиспользование ячеек DELETEDо
TEST(DoubleHashingHardcore, DeletedCellReuse) {
    HashTableDoubleHashing<int> table(5);

    table.insert("key1", 100);
    table.insert("key2", 200);

    table.erase("key1");
    EXPECT_FALSE(table.consist("key1"));

    table.insert("key1", 999);
    EXPECT_TRUE(table.consist("key1"));
    EXPECT_EQ(table.find("key1"), 999);
}

// Тест на обрыв цепочки
TEST(DoubleHashingHardcore, ChainNotBrokenByDelete) {
    HashTableDoubleHashing<int> table(7);

    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);
    table.insert("d", 4);

    table.erase("b");

    EXPECT_TRUE(table.consist("a"));
    EXPECT_TRUE(table.consist("c"));
    EXPECT_TRUE(table.consist("d"));
}

//Тест на пустую таблицу
TEST(DoubleHashingHardcore, EmptyTableOperations) {
    HashTableDoubleHashing<int> table(11);

    EXPECT_TRUE(table.is_empty());
    EXPECT_FALSE(table.consist("ghost"));
    EXPECT_THROW(table.find("ghost"), std::logic_error);
    EXPECT_THROW(table.erase("ghost"), std::logic_error);
    EXPECT_THROW(table.replace("ghost", 5), std::logic_error);
}

// тест на дубликаты
TEST(DoubleHashingHardcore, DuplicatesLogic) {
    HashTableDoubleHashing<int> table(11);
    table.insert("clone", 1);

    EXPECT_THROW(table.insert("clone", 2), std::logic_error);

    table.replace("clone", 500);
    EXPECT_EQ(table.find("clone"), 500);
}



//  Стресс-тест цепочки
TEST(ChainingHardcore, MassiveCollisions) {
    HashTableChaining<int> table(1);
    for (int i = 0; i < 1000; ++i) {
        table.insert("key" + std::to_string(i), i);
    }

    EXPECT_FALSE(table.is_empty());

    EXPECT_EQ(table.find("key0"), 0);
    EXPECT_EQ(table.find("key500"), 500);
    EXPECT_EQ(table.find("key999"), 999);
}

//Тест на удаление из разных частей вектора
TEST(ChainingHardcore, ErasePositions) {
    HashTableChaining<int> table(1);

    table.insert("head", 1);
    table.insert("mid1", 2);
    table.insert("mid2", 3);
    table.insert("tail", 4);

    table.erase("tail");
    EXPECT_FALSE(table.consist("tail"));

    table.erase("head");
    EXPECT_FALSE(table.consist("head"));

    table.erase("mid1");
    EXPECT_FALSE(table.consist("mid1"));

    EXPECT_TRUE(table.consist("mid2"));
    EXPECT_EQ(table.find("mid2"), 3);
}

//  Отсутствие переполнения
TEST(ChainingHardcore, NoOverflow) {
    HashTableChaining<int> table(2);
    EXPECT_NO_THROW({
        for (int i = 0; i < 10; ++i) {
            table.insert("val" + std::to_string(i), i);
        }
        });
}

// Тест на замену значения в цепочке
TEST(ChainingHardcore, ReplaceInChain) {
    HashTableChaining<int> table(5);

    table.insert("target", 10);
    EXPECT_EQ(table.find("target"), 10);

    table.replace("target", 999);
    EXPECT_EQ(table.find("target"), 999);
}

// Тест на удаление несуществующих ключей в непустой цепочке
TEST(ChainingHardcore, EraseGhostInPopulatedChain) {
    HashTableChaining<int> table(1);
    table.insert("real", 1);
    EXPECT_THROW(table.erase("ghost"), std::logic_error);
    EXPECT_TRUE(table.consist("real"));
}
// Проверка автоматической сортировки при вставке в случайном порядке
TEST(SortedTableOnVecTest, OrderMaintainedOnRandomInsert) {
    SortedTableOnVec<int, std::string> t;

    // Вставляем элементы вразнобой
    t.insert(50, "fifty");
    t.insert(10, "ten");
    t.insert(40, "forty");
    t.insert(20, "twenty");
    t.insert(30, "thirty");

    std::ostringstream os;
    t.print(os);
    std::string s = os.str();

    size_t p10 = s.find("10");
    size_t p20 = s.find("20");
    size_t p30 = s.find("30");
    size_t p40 = s.find("40");
    size_t p50 = s.find("50");

    // Проверяем, что в выводе ключи идут строго по возрастанию
    EXPECT_TRUE(p10 < p20 && p20 < p30 && p30 < p40 && p40 < p50);
}

// Проверка сохранения порядка после удаления элементов из разных частей вектора
TEST(SortedTableOnVecTest, OrderMaintainedAfterErase) {
    SortedTableOnVec<int, std::string> t;

    t.insert(30, "30");
    t.insert(10, "10");
    t.insert(40, "40");
    t.insert(20, "20");

    // Удаляем элемент из середины (20) и конца (40)
    t.erase(20);
    t.erase(40);

    std::ostringstream os;
    t.print(os);
    std::string s = os.str();

    size_t p10 = s.find("10");
    size_t p30 = s.find("30");

    EXPECT_TRUE(p10 < p30);
    EXPECT_EQ(s.find("20"), std::string::npos);
    EXPECT_EQ(s.find("40"), std::string::npos);
}
// Проверка упорядоченности BST после удаления корня и сложных узлов
TEST_F(TreeTableAdvancedTest, OrderIntegrityAfterComplexErase) {
    // Строим дерево
    table.insert(100, "root");
    table.insert(50, "L");
    table.insert(150, "R");
    table.insert(25, "LL");
    table.insert(75, "LR");
    table.insert(125, "RL");
    table.insert(175, "RR");

    // Удаляем корень (100) — у него два потомка
    table.erase(100);
    // Удаляем узел с одним или двумя потомками (50)
    table.erase(50);

    std::ostringstream os;
    table.print(os);
    std::string s = os.str();

    // Оставшиеся ключи: 25, 75, 125, 150, 175
    size_t p25 = s.find("25");
    size_t p75 = s.find("75");
    size_t p125 = s.find("125");
    size_t p150 = s.find("150");
    size_t p175 = s.find("175");

    // Инвариант упорядоченного обхода (In-order traversal) должен сохраняться
    EXPECT_TRUE(p25 < p75 && p75 < p125 && p125 < p150 && p150 < p175);
}
// Проверка, что балансировка (вращения) в AVL не нарушает порядок ключей
TEST_F(TableAVLAdvancedTest, SortingIntegrityAfterMassiveRotations) {
    std::vector<int> random_keys = { 15, 10, 20, 5, 12, 18, 25, 3, 8, 11, 14, 16, 19, 22, 27 };

    for (int k : random_keys) {
        table.insert(k, ".");
    }

    // Проверяем исходный порядок
    std::ostringstream os1;
    table.print(os1);
    std::string s1 = os1.str();

    // Проверяем последовательность позиций выборочно
    EXPECT_TRUE(s1.find("3") < s1.find("5"));
    EXPECT_TRUE(s1.find("12") < s1.find("14"));
    EXPECT_TRUE(s1.find("22") < s1.find("25"));

    // Теперь провоцируем серию вращений через удаление узлов
    table.erase(5);
    table.erase(20);
    table.erase(15); // Удаление корня

    std::ostringstream os2;
    table.print(os2);
    std::string s2 = os2.str();

    // Проверяем, что оставшиеся элементы всё еще идеально отсортированы
    // Оставшиеся для теста: 3, 8, 10, 11, 12, 14
    size_t p3 = s2.find("3");
    size_t p8 = s2.find("8");
    size_t p10 = s2.find("10");
    size_t p11 = s2.find("11");
    size_t p12 = s2.find("12");
    size_t p14 = s2.find("14");

    EXPECT_TRUE(p3 < p8 && p8 < p10 && p10 < p11 && p11 < p12 && p12 < p14);
}
