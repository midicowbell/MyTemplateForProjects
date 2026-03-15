#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <vector>
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
	std::string cleaned;
	for (char c : s) {
		if (!std::isspace(c)) {
			cleaned += c;
		}
	}

	std::vector<std::string> tokens;
	std::string current;

	for (size_t i = 0; i < cleaned.length(); ++i) {
		char c = cleaned[i];

		if ((c == '+' || c == '-') && i > 0) {
			if (!current.empty()) {
				tokens.push_back(current);
			}
			current = "";
			if (c == '-') {
				current = "-";
			}
		}
		else {
			current += c;
		}
	}

	if (!current.empty()) {
		tokens.push_back(current);
	}
	for (const auto& token : tokens) {
		if (token.empty()) continue;

		double coeff = 1.0;
		int degX = 0, degY = 0, degZ = 0;

		if (std::isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && std::isdigit(token[1]))) {
			size_t i = 0;
			if (token[0] == '-') i++;

			while (i < token.length() && (std::isdigit(token[i]) || token[i] == '.')) {
				i++;
			}

			coeff = std::stod(token.substr(0, i));
			std::string varPart = token.substr(i);
			parseVariablesFromString(varPart, degX, degY, degZ);
		}
		else if (token[0] == '-') {
			coeff = -1;
			parseVariablesFromString(token.substr(1), degX, degY, degZ);
		}
		else if (std::isalpha(token[0])) {
			coeff = 1;
			parseVariablesFromString(token, degX, degY, degZ);
		}

		addMonom(Monom(coeff, degX, degY, degZ));
	}
}

void Polynom::parseVariablesFromString(const std::string& s, int& degX, int& degY, int& degZ) const {
	for (size_t i = 0; i < s.length(); ++i) {
		char c = s[i];

		if (c == 'x') {
			if (i + 1 < s.length() && s[i + 1] == '^') {
				size_t j = i + 2;
				while (j < s.length() && std::isdigit(s[j])) {
					j++;
				}
				degX = std::stoi(s.substr(i + 2, j - i - 2));
				i = j - 1;
			}
			else {
				degX = 1;
			}
		}
		else if (c == 'y') {
			if (i + 1 < s.length() && s[i + 1] == '^') {
				size_t j = i + 2;
				while (j < s.length() && std::isdigit(s[j])) {
					j++;
				}
				degY = std::stoi(s.substr(i + 2, j - i - 2));
				i = j - 1;
			}
			else {
				degY = 1;
			}
		}
		else if (c == 'z') {
			if (i + 1 < s.length() && s[i + 1] == '^') {
				size_t j = i + 2;
				while (j < s.length() && std::isdigit(s[j])) {
					j++;
				}
				degZ = std::stoi(s.substr(i + 2, j - i - 2));
				i = j - 1;
			}
			else {
				degZ = 1;
			}
		}
	}
}


void Polynom::addMonom(const Monom& m) {
	if (m.getCoeff() == 0.0)
		return;

	int pos = 0;
	for (auto it = monoms.begin(); it != monoms.end(); ++it, ++pos) {
		if (it->getDegX() == m.getDegX() &&
			it->getDegY() == m.getDegY() &&
			it->getDegZ() == m.getDegZ()) {

			*it += m;

			if (it->getCoeff() == 0.0)
				monoms.erase(pos);

			return;
		}
		if (m > *it) {
			monoms.insert(pos, m);
			return;
		}
	}

	monoms.push_back(m);
}

Polynom Polynom::operator+(const Polynom& other) {
	Polynom result(*this);
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().end(); ++it) {
		result = result + (*it);
	}
	return result;
}
Polynom Polynom::operator-(const Polynom& other) {
	Polynom result(*this);
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().end(); ++it) {
		result = result - (*it);
	}
	return result;
}

Polynom Polynom::operator*(const Polynom& other) {
	Polynom result;
	for (auto it1 = other.getMonoms().begin(); it1 != other.getMonoms().end(); ++it1) {
		result += (*this)  * (*it1);
		}
	return result;
	}
	

Polynom Polynom::operator*(const Monom& other) {
	Polynom result;
	for (auto it1 = this->getMonoms().begin(); it1 != this->getMonoms().end(); ++it1) {
		Monom m(it1->getCoeff() * other.getCoeff(),
			it1->getDegX() + other.getDegX(),
			it1->getDegY() + other.getDegY(),
			it1->getDegZ() + other.getDegZ());
		result.addMonom(m);
	}
	return result;

}

Polynom Polynom::operator+(const Monom& other) {
	Polynom result(*this);
	result.addMonom(other);
	return result;
}
Polynom Polynom::operator-(const Monom& other)  {
	Polynom result(*this);
	Monom neg = other;
	neg.setCoeff(-neg.getCoeff()); 
	result.addMonom(neg);          
	return result;
}
Polynom Polynom::operator/(const Monom& other) {
	if (other.getCoeff() == 0.0) {
		throw std::invalid_argument("Division by zero");
	}
	for (auto it = monoms.begin(); it != monoms.end(); ++it) {
		if (!it->isValidDivision(other)) {
			throw std::logic_error("Division results in negative degrees");
		}
	}
	Polynom result;
	for (auto it1 = this->getMonoms().begin(); it1 != this->getMonoms().end(); ++it1) {
		Monom m(it1->getCoeff() / other.getCoeff(),
			it1->getDegX() - other.getDegX(),
			it1->getDegY() - other.getDegY(),
			it1->getDegZ() - other.getDegZ());
		result.addMonom(m);
	}
	return result;
}

Polynom Polynom::operator/(const Polynom& other) {
	throw std::logic_error("Polynomial division is not implemented");
}
Polynom& Polynom::operator+=(const Monom& other) {
	this->addMonom(other);
	return *this;
}

Polynom& Polynom::operator-=(const Monom& other) {
	Monom neg = other;
	neg.setCoeff(-neg.getCoeff());
	this->addMonom(neg);
	return *this;
}

Polynom& Polynom::operator+=(const Polynom& other) {
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().end(); ++it) {
		*this += *it; 
	}
	return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().end(); ++it) {
		*this -= *it;
	}
	return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) {
	Polynom temp;
	for (auto it1 = this->getMonoms().begin(); it1 != this->getMonoms().end(); ++it1) {
		for (auto it2 = other.getMonoms().begin(); it2 != other.getMonoms().end(); ++it2) {
			Monom m(it1->getCoeff() * it2->getCoeff(),
				it1->getDegX() + it2->getDegX(),
				it1->getDegY() + it2->getDegY(),
				it1->getDegZ() + it2->getDegZ());
			temp.addMonom(m);
		}
	}
	monoms = temp.monoms;
	return *this;
}

Polynom& Polynom::operator/=(const Polynom& other) {
	throw std::logic_error("Polynomial division is not implemented");
}

Polynom Polynom::operator*(double k) const {
	Polynom result;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() * k);
		result.addMonom(m);
	}
	return result;
}

Polynom Polynom::operator/(double k) const {
	if (k == 0) throw std::logic_error("Division by zero");
	Polynom result;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() / k);
		result.addMonom(m);
	}
	return result;
}

Polynom& Polynom::operator*=(double k) {
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		const_cast<Monom&>(*it).setCoeff(it->getCoeff() * k);
	}
	return *this;
}

Polynom& Polynom::operator/=(double k) {
	if (k == 0) throw std::logic_error("Division by zero");
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		const_cast<Monom&>(*it).setCoeff(it->getCoeff() / k);
	}
	return *this;
}

double Polynom::value(double x, double y, double z) const {
	double result = 0.0;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		result += it->value(x, y, z);
	}
	return result;
}