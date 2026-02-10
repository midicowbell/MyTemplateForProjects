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


//
// +=
//
TEST(MonomPlusEqual, AddSimilarMonoms) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 2, 1, 0);

    a += b;

    EXPECT_DOUBLE_EQ(a.getCoef(), 8.0);
    EXPECT_EQ(a.getDegX(), 2);
    EXPECT_EQ(a.getDegY(), 1);
    EXPECT_EQ(a.getDegZ(), 0);
}

TEST(MonomPlusEqual, AddDifferentDegreesThrows) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 3, 1, 0);

    EXPECT_THROW(a += b, std::invalid_argument);
}

//
// -=
//
TEST(MonomMinusEqual, SubtractSimilarMonoms) {
    Monom a(8.0, 2, 1, 0);
    Monom b(5.0, 2, 1, 0);

    a -= b;

    EXPECT_DOUBLE_EQ(a.getCoef(), 3.0);
    EXPECT_EQ(a.getDegX(), 2);
    EXPECT_EQ(a.getDegY(), 1);
    EXPECT_EQ(a.getDegZ(), 0);
}

TEST(MonomMinusEqual, SubtractDifferentDegreesThrows) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 3, 1, 0);

    EXPECT_THROW(a -= b, std::invalid_argument);
}

//
// *= (monom)
//
TEST(MonomMulEqual, MultiplyMonoms) {
    Monom a(3.0, 2, 1, 0);
    Monom b(4.0, 1, 2, 3);

    a *= b;

    EXPECT_DOUBLE_EQ(a.getCoef(), 12.0);
    EXPECT_EQ(a.getDegX(), 3);
    EXPECT_EQ(a.getDegY(), 3);
    EXPECT_EQ(a.getDegZ(), 3);
}

//
// /= (monom)
//
TEST(MonomDivEqual, DivideMonoms) {
    Monom a(12.0, 3, 3, 3);
    Monom b(3.0, 1, 1, 1);

    a /= b;

    EXPECT_DOUBLE_EQ(a.getCoef(), 4.0);
    EXPECT_EQ(a.getDegX(), 2);
    EXPECT_EQ(a.getDegY(), 2);
    EXPECT_EQ(a.getDegZ(), 2);
}

TEST(MonomDivEqual, DivideByZeroCoefThrows) {
    Monom a(5.0, 2, 2, 2);
    Monom b(0.0, 1, 1, 1);

    EXPECT_THROW(a /= b, std::invalid_argument);
}

TEST(MonomDivEqual, NegativeDegreeThrows) {
    Monom a(5.0, 1, 1, 1);
    Monom b(2.0, 2, 0, 0);

    EXPECT_THROW(a /= b, std::invalid_argument);
}

//
// / value
//
TEST(MonomValue, SimpleValue) {
    Monom m(3.0, 2, 1, 0); // 3 * x^2 * y^1 * z^0

    double result = m.value(2.0, 3.0, 10.0);

    // 3 * (2^2) * (3^1) * (10^0) = 3 * 4 * 3 * 1 = 36
    EXPECT_DOUBLE_EQ(result, 36.0);
}

TEST(MonomValue, ZeroCoefficient) {
    Monom m(0.0, 5, 5, 5);

    double result = m.value(10.0, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(MonomValue, ZeroVariables) {
    Monom m(4.0, 3, 2, 1); // 4 * x^3 * y^2 * z^1

    double result = m.value(0.0, 5.0, 7.0);

    // 4 * 0^3 * 5^2 * 7^1 = 0
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(MonomValue, AllPowersZero) {
    Monom m(7.0, 0, 0, 0); // константа

    double result = m.value(100.0, 200.0, 300.0);

    EXPECT_DOUBLE_EQ(result, 7.0);
}
TEST(MonomIO, OutputOperator) {
    Monom m(3.5, 2, 1, 0);

    std::stringstream ss;
    ss << m;

    EXPECT_EQ(ss.str(), "3.5 * x^2 * y^1 * z^0");
}
TEST(MonomIO, InputOperator) {
    std::stringstream ss("4.2 3 2 1");

    Monom m;
    ss >> m;

    EXPECT_DOUBLE_EQ(m.getCoef(), 4.2);
    EXPECT_EQ(m.getDegX(), 3);
    EXPECT_EQ(m.getDegY(), 2);
    EXPECT_EQ(m.getDegZ(), 1);
}
//
// == и !=
//
TEST(MonomCompare, Equal) {
    Monom a(3.0, 1, 2, 3);
    Monom b(3.0, 1, 2, 3);
    EXPECT_TRUE(a == b);
}

TEST(MonomCompare, NotEqual) {
    Monom a(3.0, 1, 2, 3);
    Monom b(4.0, 1, 2, 3);
    EXPECT_TRUE(a != b);
}

//
// + и +=
//
TEST(MonomPlus, AddSimilar) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 2, 1, 0);
    Monom c = a + b;
    EXPECT_DOUBLE_EQ(c.getCoef(), 8.0);
}

TEST(MonomPlus, AddDifferentThrows) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 3, 1, 0);
    EXPECT_THROW(a + b, std::invalid_argument);
}

TEST(MonomPlusEqual, AddSimilar) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 2, 1, 0);
    a += b;
    EXPECT_DOUBLE_EQ(a.getCoef(), 8.0);
}

TEST(MonomPlusEqual, AddDifferentThrows) {
    Monom a(3.0, 2, 1, 0);
    Monom b(5.0, 3, 1, 0);
    EXPECT_THROW(a += b, std::invalid_argument);
}
TEST(MonomScalarOps, MulScalar) {
    Monom m(3.0, 2, 1, 0);

    Monom r = m * 2.0;

    EXPECT_DOUBLE_EQ(r.getCoef(), 6.0);
    EXPECT_EQ(r.getDegX(), 2);
    EXPECT_EQ(r.getDegY(), 1);
    EXPECT_EQ(r.getDegZ(), 0);
}

TEST(MonomScalarOps, DivScalar) {
    Monom m(6.0, 2, 1, 0);

    Monom r = m / 2.0;

    EXPECT_DOUBLE_EQ(r.getCoef(), 3.0);
    EXPECT_EQ(r.getDegX(), 2);
    EXPECT_EQ(r.getDegY(), 1);
    EXPECT_EQ(r.getDegZ(), 0);
}

TEST(MonomScalarOps, DivScalarThrowsOnZero) {
    Monom m(6.0, 2, 1, 0);

    EXPECT_THROW(m / 0.0, std::invalid_argument);
}

TEST(MonomScalarOps, MulScalarInPlace) {
    Monom m(3.0, 2, 1, 0);

    m *= 2.0;

    EXPECT_DOUBLE_EQ(m.getCoef(), 6.0);
}

TEST(MonomScalarOps, DivScalarInPlace) {
    Monom m(6.0, 2, 1, 0);

    m /= 2.0;

    EXPECT_DOUBLE_EQ(m.getCoef(), 3.0);
}

TEST(MonomScalarOps, DivScalarInPlaceThrowsOnZero) {
    Monom m(6.0, 2, 1, 0);

    EXPECT_THROW(m /= 0.0, std::invalid_argument);
}
