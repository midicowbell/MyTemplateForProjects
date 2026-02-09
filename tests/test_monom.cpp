#include <gtest/gtest.h>
#include "monom.h" 
#include "polynom.h"

// --- Тест обычного конструктора ---
TEST(MonomConstructor, BasicConstructorSetsValuesCorrectly) {
    Monom m(3.5, 2, 1, 0);

    EXPECT_DOUBLE_EQ(m.getCoef(), 3.5);
    EXPECT_EQ(m.getDegX(), 2);
    EXPECT_EQ(m.getDegY(), 1);
    EXPECT_EQ(m.getDegZ(), 0);
}

// --- Тест конструктора копирования ---
TEST(MonomConstructor, CopyConstructorCopiesAllFields) {
    Monom original(7.0, 4, 3, 2);
    Monom copy(original);

    EXPECT_DOUBLE_EQ(copy.getCoef(), 7.0);
    EXPECT_EQ(copy.getDegX(), 4);
    EXPECT_EQ(copy.getDegY(), 3);
    EXPECT_EQ(copy.getDegZ(), 2);
}

// --- Равные мономы ---
TEST(MonomComparison, EqualMonomsAreRecognized) {
    Monom a(3.0, 2, 1, 0);
    Monom b(3.0, 2, 1, 0);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

// --- Разные коэффициенты ---
TEST(MonomComparison, DifferentCoefMeansNotEqual) {
    Monom a(3.0, 2, 1, 0);
    Monom b(4.0, 2, 1, 0);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

// --- Разные степени ---
TEST(MonomComparison, DifferentDegreesMeansNotEqual) {
    Monom a(3.0, 2, 1, 0);
    Monom b(3.0, 2, 2, 0);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

// --- Полностью разные ---
TEST(MonomComparison, CompletelyDifferentMonomsAreNotEqual) {
    Monom a(1.0, 1, 1, 1);
    Monom b(5.0, 3, 2, 0);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}
// --- Сложение одинаковых мономов ---
TEST(MonomAddition, AddSimilarMonoms) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 2, 1, 0);

    Monom c = a + b;

    EXPECT_DOUBLE_EQ(c.getCoef(), 8.0);
    EXPECT_EQ(c.getDegX(), 2);
    EXPECT_EQ(c.getDegY(), 1);
    EXPECT_EQ(c.getDegZ(), 0);
}

// --- Сложение мономов с разными степенями должно бросать исключение ---
TEST(MonomAddition, AddDifferentDegreesThrows) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 3, 1, 0); // степень по X другая

    EXPECT_THROW(a + b, std::invalid_argument);
}
// --- Вычитание одинаковых мономов ---
TEST(MonomSubtraction, SubtractSimilarMonoms) {
    Monom a(8.0, 2, 1, 0);
    Monom b(5.0, 2, 1, 0);

    Monom c = a - b;

    EXPECT_DOUBLE_EQ(c.getCoef(), 3.0);
    EXPECT_EQ(c.getDegX(), 2);
    EXPECT_EQ(c.getDegY(), 1);
    EXPECT_EQ(c.getDegZ(), 0);
}

// --- Вычитание мономов с разными степенями ---
TEST(MonomSubtraction, SubtractDifferentDegreesThrows) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 3, 1, 0); // степень по X другая

    EXPECT_THROW(a - b, std::invalid_argument);
}
// --- Умножение двух мономов ---
TEST(MonomMultiplication, MultiplyTwoMonoms) {
    Monom a(3.0, 2, 1, 0);
    Monom b(4.0, 1, 2, 3);

    Monom c = a * b;

    EXPECT_DOUBLE_EQ(c.getCoef(), 12.0); // 3 * 4
    EXPECT_EQ(c.getDegX(), 3);           // 2 + 1
    EXPECT_EQ(c.getDegY(), 3);           // 1 + 2
    EXPECT_EQ(c.getDegZ(), 3);           // 0 + 3
}

// --- Умножение на моном с нулевым коэффициентом ---
TEST(MonomMultiplication, MultiplyByZeroCoef) {
    Monom a(5.0, 1, 1, 1);
    Monom b(0.0, 3, 3, 3);

    Monom c = a * b;

    EXPECT_DOUBLE_EQ(c.getCoef(), 0.0);
    EXPECT_EQ(c.getDegX(), 4);
    EXPECT_EQ(c.getDegY(), 4);
    EXPECT_EQ(c.getDegZ(), 4);
}

// --- Умножение на единичный моном ---
TEST(MonomMultiplication, MultiplyByOneMonom) {
    Monom a(7.0, 2, 2, 2);
    Monom b(1.0, 0, 0, 0);

    Monom c = a * b;

    EXPECT_DOUBLE_EQ(c.getCoef(), 7.0);
    EXPECT_EQ(c.getDegX(), 2);
    EXPECT_EQ(c.getDegY(), 2);
    EXPECT_EQ(c.getDegZ(), 2);
}
TEST(MonomDivision, DivideTwoMonoms) {
    Monom a(12.0, 3, 3, 3);
    Monom b(3.0, 1, 1, 1);

    Monom c = a / b;

    EXPECT_DOUBLE_EQ(c.getCoef(), 4.0); // 12 / 3
    EXPECT_EQ(c.getDegX(), 2);          // 3 - 1
    EXPECT_EQ(c.getDegY(), 2);
    EXPECT_EQ(c.getDegZ(), 2);
}
TEST(MonomDivision, DivideByZeroCoefThrows) {
    Monom a(5.0, 2, 2, 2);
    Monom b(0.0, 1, 1, 1);

    EXPECT_THROW(a / b, std::invalid_argument);
}
TEST(MonomDivision, NegativeDegreeThrows) {
    Monom a(5.0, 1, 1, 1);
    Monom b(2.0, 2, 0, 0); // степень X больше

    EXPECT_THROW(a / b, std::invalid_argument);
}

