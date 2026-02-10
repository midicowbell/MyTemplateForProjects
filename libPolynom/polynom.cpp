#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include "monom.h"
#include "polynom.h"
#include "ListDoubly.h"
Polynom::Polynom() {
	monoms = ListDoubly<Monom>();
}
Polynom::Polynom(const Polynom& other) {
	monoms = other.monoms;
}
Polynom::Polynom(const std::string& s) {
	std::string str = s;
	for (int i = 0; i < s.size(); ++i) {
		if (str[i] == '-') {
			str.insert(i, "+");
			++i;
		}
	}
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, '+')) {
		if (token.empty()) continue;
		double coeff = 1;
		int degX = 0; int degY = 0; int degZ = 0;
		std::stringstream t(token);
		if (std::isdigit(token[0]) || token[0] != '-') {
			t >> coeff;
		}
		char c;
		while (t >> c) {
			if (c == 'x') {
				if (t.peek() == '^') {
					t.get(); t >> degX;
				}
				else { degX = 1; }
			}
			if (c == 'y') {
				if (t.peek() == '^') {
					t.get(); t >> degY;
				}
				else { degY = 1; }
			}
			if (c == 'z') {
				if (t.peek() == '^') {
					t.get(); t >> degZ;
				}
				else { degZ = 1; }
			}
		}
		addMonom(Monom(coeff, degX, degY, degZ));
	}
}
void Polynom::addMonom(const Monom& m) {
	if (m.getCoef() == 0.0)
		return;

	int pos = 0;

	for (auto it = monoms.begin(); it != monoms.end(); ++it, ++pos) {

		// одинаковые степени → складываем
		if (it->getDegX() == m.getDegX() &&
			it->getDegY() == m.getDegY() &&
			it->getDegZ() == m.getDegZ()) {

			*it += m;

			if (it->getCoef() == 0.0)
				monoms.erase(pos);

			return;
		}

		// сортировка по степеням
		if (m > *it) { // если хочешь — замени на свой compare
			monoms.insert(pos, m);
			return;
		}
	}

	monoms.push_back(m);
}

