#pragma once
#include <string>

class Parser {
private:
	std::string string_;
public:
	Parser(std::string);
	bool isDigit(int) const;
	double toDigit(char) const;
	double findNumber(int&, bool) const;
	std::string findOperation(int, int) const;
	bool isUnaryMinus(char) const;
};