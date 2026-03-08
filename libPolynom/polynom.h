#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "ListDoubly.h"
#include "monom.h"

class Polynom {
private:
	ListDoubly<Monom> monoms;

	void parseVariablesFromString(const std::string& s, int& degX, int& degY, int& degZ) const;

public:
	Polynom();
	Polynom(const Polynom& other);
	Polynom(const std::string& str);

	void addMonom(const Monom& m);

	Polynom operator+(const Polynom& other);
	Polynom operator-(const Polynom& other);
	Polynom operator*(const Polynom& other);
	Polynom operator/(const Polynom& other);
	Polynom& operator+=(const Polynom& other);
	Polynom& operator-=(const Polynom& other);
	Polynom& operator*=(const Polynom& other);
	Polynom& operator/=(const Polynom& other);
	Polynom operator*(double k) const;
	Polynom operator/(double k) const;
	Polynom& operator*=(double k);
	Polynom& operator/=(double k);

	double value(double x, double y, double z) const;

	const ListDoubly<Monom>& getMonoms() const { return monoms; }
};