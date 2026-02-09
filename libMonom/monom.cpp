#include <iostream>
#include <stdexcept>
#include <cmath>
#include "monom.h"
Monom::Monom(double c, int degX, int degY, int degZ) {
	coeff = c;
	deg[0] = degX;
	deg[1] = degY;
	deg[2] = degZ;
}

Monom::Monom(const Monom& other) {
	for (int i = 0; i < 3; i++) {
		deg[i] = other.deg[i];
	}
	coeff = other.coeff;
}
bool Monom::operator==(const Monom& other) const {
	return coeff == other.getCoef() && deg[0] == other.getDegX() && deg[1] == other.getDegY() && deg[2] == other.getDegZ();

}
bool Monom::operator!=(const Monom& other) const {
	return !(*this == other);
}
Monom Monom::operator+(const Monom& other) const {
	if (deg[0] != other.getDegX() || deg[1] != other.getDegY() || deg[2] != other.getDegZ()) {
		throw std::invalid_argument("Cannot add monoms with different degrees");
	}
	return Monom(coeff + other.getCoef(), deg[0], deg[1], deg[2]);
}
Monom Monom::operator-(const Monom& other) const {
	if (deg[0] != other.getDegX() || deg[1] != other.getDegY() || deg[2] != other.getDegZ()) {
		throw std::invalid_argument("Cannot subtract monoms with different degrees");

	}
	return Monom(coeff - other.getCoef(), deg[0], deg[1], deg[2]);
}
Monom Monom::operator*(const Monom& other) const {
	return Monom(coeff * other.getCoef(), deg[0] + other.getDegX(), deg[1] + other.getDegY(), deg[2] + other.getDegZ());
}
Monom Monom::operator/(const Monom& other) const {
	if (other.getCoef() == 0.0) {
		throw std::invalid_argument("Cannot divide by monom with zero coefficient");
	}

	if (deg[0] < other.getDegX() ||
		deg[1] < other.getDegY() ||
		deg[2] < other.getDegZ()) {
		throw std::invalid_argument("Resulting monom has negative degree");
	}

	return Monom(coeff / other.getCoef(),
		deg[0] - other.getDegX(),
		deg[1] - other.getDegY(),
		deg[2] - other.getDegZ());
}
