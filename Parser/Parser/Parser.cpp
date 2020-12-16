#include "pch.h"
#include "framework.h"
#include "../../LibsH/Parser.h"

Parser::Parser(std::string s) {
	string_ = s;
}

bool Parser::isDigit(int ind) const {
	if (string_[ind] >= '0' && string_[ind] <= '9') {
		return true;
	}
	return false;
}

double Parser::toDigit(char c) const {
	return static_cast<double>(c) - '0';
}

double Parser::findNumber(int& ind, bool negNumbersFlag) const {
	int i = ind;
	double res = 0;
	bool flagOfdouble = false;

	int firstInd = ind;

	if (ind == string_.size() - 1) {
		return toDigit(string_[ind++]);
	}
	do {
		++i;

		if (string_[i] == '.') {
			int temp = i - 1;
			int degree = 0;
			while (temp >= 0 && isDigit(temp)) {
				res += toDigit(string_[temp]) * std::pow(10, degree);
				--temp;
				++degree;
			}

			temp = i + 1;
			degree = -1;
			while (temp < string_.size() && isDigit(temp)) {
				res += toDigit(string_[temp]) * std::pow(10, degree);
				++temp;
				--degree;
			}
			ind = temp;
			flagOfdouble = true;

			if (negNumbersFlag && isUnaryMinus(string_[firstInd])) {
				res *= -1;
			}

			return res;
		}
	} while (i < string_.size() && isDigit(i));

	ind = i;

	if (!flagOfdouble) {
		--i;
		int degree = 0;
		while (i >= 0 && isDigit(i)) {
			res += toDigit(string_[i]) * std::pow(10, degree);
			--i;
			++degree;
		}
	}

	if (negNumbersFlag && isUnaryMinus(string_[firstInd])) {
		res *= -1;
	}

	return res;
}

std::string Parser::findOperation(int ind, int border) const {
	std::string op;
	int temp = 0;
	while (ind >= border && !isDigit(ind) && string_[ind] != '(' && string_[ind] != ')') {
		temp++;
		--ind;
	}
	op = string_.substr(ind + 1, temp);
	return op;
}

bool Parser::isUnaryMinus(char c) const {
	return (c == '-');
}