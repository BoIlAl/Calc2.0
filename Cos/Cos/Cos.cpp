#include "pch.h"
#include "Cos.h"

bool Cos::IsThatOp(const std::string& s) const {
	if (s == "cos") {
		return true;
	}
	return false;
}

int Cos::getPriority() const {
	return c_priority;
}

Associativity Cos::getAssociativity() const {
	return c_associativity;
}

ERROR_ Cos::count(const std::string& expression, double& answer) {
	parser_ = new Parser(expression);

	if (expression.size() < 4 || !(expression[0] == 'c' && expression[1] == 'o' && expression[2] == 's')) {
		return E_ERROR;
	}
	int temp = 3;
	if (!parser_->isDigit(temp) && !parser_->isUnaryMinus(expression[temp])) {
		return E_ERROR;
	}
	double operand = parser_->findNumber(temp, true);

	if (temp != expression.size()) {
		return E_ERROR;
	}

	answer = std::cos(operand);

	delete parser_;
	return E_OK;
}

AbstractOperation* getOperation() {
	return new Cos();
}