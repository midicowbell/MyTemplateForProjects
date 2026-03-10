#include <gtest/gtest.h>
#include "polynom.h"
#include "monom.h"

// ---------- ТЕСТЫ КОНСТРУКТОРОВ ----------

TEST(PolynomTest, DefaultConstructorCreatesEmpty) {
    Polynom p;
    EXPECT_EQ(p.getMonoms().size(), 0);
}

TEST(PolynomTest, CopyConstructorCopiesMonoms) {
    Polynom p1;
    p1.addMonom(Monom(5, 2, 0, 0));
    p1.addMonom(Monom(3, 1, 0, 0));

    Polynom p2(p1);

    EXPECT_EQ(p2.getMonoms().size(), 2);

    auto it1 = p1.getMonoms().begin();
    auto it2 = p2.getMonoms().begin();

    EXPECT_EQ(it1->getCoeff(), it2->getCoeff());
    EXPECT_EQ(it1->getDegX(), it2->getDegX());
}

TEST(PolynomTest, StringConstructorParsesMonoms) {
    Polynom p("3x^2 + 2x - 5");

    EXPECT_EQ(p.getMonoms().size(), 3);

    bool hasX2 = false, hasX1 = false, hasConst = false;

    for (auto it = p.getMonoms().begin(); it != p.getMonoms().end(); ++it) {
        if (it->getDegX() == 2 && it->getCoeff() == 3) hasX2 = true;
        if (it->getDegX() == 1 && it->getCoeff() == 2) hasX1 = true;
        if (it->getDegX() == 0 && it->getCoeff() == -5) hasConst = true;
    }

    EXPECT_TRUE(hasX2);
    EXPECT_TRUE(hasX1);
    EXPECT_TRUE(hasConst);
}

// ---------- ТЕСТЫ addMonom ----------

TEST(PolynomTest, AddMonomSimple) {
    Polynom p;
    p.addMonom(Monom(5, 2, 0, 0));

    EXPECT_EQ(p.getMonoms().size(), 1);

    auto it = p.getMonoms().begin();
    EXPECT_DOUBLE_EQ(it->getCoeff(), 5);
    EXPECT_EQ(it->getDegX(), 2);
}

TEST(PolynomTest, AddMonomCombineSameDegrees) {
    Polynom p;
    p.addMonom(Monom(3, 1, 2, 3));
    p.addMonom(Monom(4, 1, 2, 3));

    EXPECT_EQ(p.getMonoms().size(), 1);

    auto it = p.getMonoms().begin();
    EXPECT_DOUBLE_EQ(it->getCoeff(), 7);
}

TEST(PolynomTest, AddMonomRemoveZero) {
    Polynom p;
    p.addMonom(Monom(3, 1, 2, 3));
    p.addMonom(Monom(-3, 1, 2, 3));

    EXPECT_EQ(p.getMonoms().size(), 0);
}

TEST(PolynomTest, AddMonomSortedInsert) {
    Polynom p;
    p.addMonom(Monom(1, 1, 0, 0)); // x
    p.addMonom(Monom(1, 3, 0, 0)); // x^3
    p.addMonom(Monom(1, 2, 0, 0)); // x^2

    auto it = p.getMonoms().begin();
    EXPECT_EQ(it->getDegX(), 3);

    ++it;
    EXPECT_EQ(it->getDegX(), 2);

    ++it;
    EXPECT_EQ(it->getDegX(), 1);
}

TEST(PolynomTest, AddMonomInsertAtEnd) {
    Polynom p;
    p.addMonom(Monom(1, 5, 0, 0));
    p.addMonom(Monom(1, 1, 0, 0));

    auto it = p.getMonoms().begin();
    EXPECT_EQ(it->getDegX(), 5);
    ++it;
    EXPECT_EQ(it->getDegX(), 1);
}

// ----------------------
//  operator+
// ----------------------

TEST(PolynomOperators, PlusSimple) {
    Polynom p1;
    p1.addMonom(Monom(3, 1, 0, 0)); // 3x
    p1.addMonom(Monom(2, 0, 0, 0)); // 2

    Polynom p2;
    p2.addMonom(Monom(5, 1, 0, 0)); // 5x
    p2.addMonom(Monom(-1, 0, 0, 0)); // -1

    Polynom p3 = p1 + p2;

    auto it = p3.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 8);  // 3x + 5x
    EXPECT_EQ(it->getDegX(), 1);

    ++it;
    EXPECT_EQ(it->getCoeff(), 1);  // 2 + (-1)
    EXPECT_EQ(it->getDegX(), 0);
}

TEST(PolynomOperators, PlusEqual) {
    Polynom p1;
    p1.addMonom(Monom(3, 1, 0, 0));
    p1.addMonom(Monom(2, 0, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(5, 1, 0, 0));
    p2.addMonom(Monom(-1, 0, 0, 0));

    p1 += p2;

    auto it = p1.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 8);
    ++it;
    EXPECT_EQ(it->getCoeff(), 1);
}

// ----------------------
//  operator-
// ----------------------

TEST(PolynomOperators, MinusSimple) {
    Polynom p1;
    p1.addMonom(Monom(3, 1, 0, 0)); // 3x
    p1.addMonom(Monom(2, 0, 0, 0)); // 2

    Polynom p2;
    p2.addMonom(Monom(1, 1, 0, 0)); // x
    p2.addMonom(Monom(5, 0, 0, 0)); // 5

    Polynom p3 = p1 - p2;

    auto it = p3.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 2); // 3x - x
    ++it;
    EXPECT_EQ(it->getCoeff(), -3); // 2 - 5
}

TEST(PolynomOperators, MinusEqual) {
    Polynom p1;
    p1.addMonom(Monom(3, 1, 0, 0));
    p1.addMonom(Monom(2, 0, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(1, 1, 0, 0));
    p2.addMonom(Monom(5, 0, 0, 0));

    p1 -= p2;

    auto it = p1.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 2);
    ++it;
    EXPECT_EQ(it->getCoeff(), -3);
}

// ----------------------
//  operator* (polynom × polynom)
// ----------------------

TEST(PolynomOperators, MultiplyPolynomials) {
    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0)); // 2x
    p1.addMonom(Monom(3, 0, 0, 0)); // 3

    Polynom p2;
    p2.addMonom(Monom(4, 1, 0, 0)); // 4x
    p2.addMonom(Monom(1, 0, 0, 0)); // 1

    // (2x + 3)(4x + 1) = 8x^2 + 2x + 12x + 3 = 8x^2 + 14x + 3
    Polynom p3 = p1 * p2;

    auto it = p3.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 8); // x^2

    ++it;
    EXPECT_EQ(it->getCoeff(), 14); // x

    ++it;
    EXPECT_EQ(it->getCoeff(), 3); // const
}

TEST(PolynomOperators, MultiplyEqualPolynomials) {
    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));
    p1.addMonom(Monom(3, 0, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(4, 1, 0, 0));
    p2.addMonom(Monom(1, 0, 0, 0));

    p1 *= p2;

    auto it = p1.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 8);
    ++it;
    EXPECT_EQ(it->getCoeff(), 14);
    ++it;
    EXPECT_EQ(it->getCoeff(), 3);
}

// ----------------------
//  operator*(double)
// ----------------------

TEST(PolynomOperators, MultiplyByScalar) {
    Polynom p;
    p.addMonom(Monom(3, 2, 0, 0)); // 3x^2
    p.addMonom(Monom(-1, 0, 0, 0)); // -1

    Polynom r = p * 2.0;

    auto it = r.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 6); // 3*2
    ++it;
    EXPECT_EQ(it->getCoeff(), -2); // -1*2
}

TEST(PolynomOperators, MultiplyEqualScalar) {
    Polynom p;
    p.addMonom(Monom(3, 2, 0, 0));
    p.addMonom(Monom(-1, 0, 0, 0));

    p *= 2.0;

    auto it = p.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 6);
    ++it;
    EXPECT_EQ(it->getCoeff(), -2);
}

// ----------------------
//  operator/(double)
// ----------------------

TEST(PolynomOperators, DivideByScalar) {
    Polynom p;
    p.addMonom(Monom(6, 2, 0, 0));
    p.addMonom(Monom(-4, 0, 0, 0));

    Polynom r = p / 2.0;

    auto it = r.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 3);
    ++it;
    EXPECT_EQ(it->getCoeff(), -2);
}

TEST(PolynomOperators, DivideEqualScalar) {
    Polynom p;
    p.addMonom(Monom(6, 2, 0, 0));
    p.addMonom(Monom(-4, 0, 0, 0));

    p /= 2.0;

    auto it = p.getMonoms().begin();
    EXPECT_EQ(it->getCoeff(), 3);
    ++it;
    EXPECT_EQ(it->getCoeff(), -2);
}
