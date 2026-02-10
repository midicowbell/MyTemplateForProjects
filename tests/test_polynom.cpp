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

    EXPECT_EQ(it1->getCoef(), it2->getCoef());
    EXPECT_EQ(it1->getDegX(), it2->getDegX());
}

TEST(PolynomTest, StringConstructorParsesMonoms) {
    Polynom p("3x^2 + 2x - 5");

    EXPECT_EQ(p.getMonoms().size(), 3);

    bool hasX2 = false, hasX1 = false, hasConst = false;

    for (auto it = p.getMonoms().begin(); it != p.getMonoms().end(); ++it) {
        if (it->getDegX() == 2 && it->getCoef() == 3) hasX2 = true;
        if (it->getDegX() == 1 && it->getCoef() == 2) hasX1 = true;
        if (it->getDegX() == 0 && it->getCoef() == -5) hasConst = true;
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
    EXPECT_DOUBLE_EQ(it->getCoef(), 5);
    EXPECT_EQ(it->getDegX(), 2);
}

TEST(PolynomTest, AddMonomCombineSameDegrees) {
    Polynom p;
    p.addMonom(Monom(3, 1, 2, 3));
    p.addMonom(Monom(4, 1, 2, 3));

    EXPECT_EQ(p.getMonoms().size(), 1);

    auto it = p.getMonoms().begin();
    EXPECT_DOUBLE_EQ(it->getCoef(), 7);
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
