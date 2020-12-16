#include "pch.h"
#include "Factorial.h"

Associativity Factorial::getAssociativity() const {
	return c_associativity;
}

bool Factorial::IsThatOp(const std::string& s) const {
	if (s == "!") {
		return true;
	}
	return false;
}

int Factorial::getPriority() const {
	return c_priority;
}

ERROR_ Factorial::count(const std::string& expression, double& answer) {
	parser_ = new Parser(expression);

	if (expression[expression.size() - 1] != '!') {
		return E_ERROR;
	}

	int temp = 0;
	double operand = parser_->findNumber(temp, true);

	if (temp != expression.size() - 1) {
		return E_ERROR;
	}

	double eps = 1e-13;
	if (operand >= 100.0 || abs(floor(operand + 0.5) - operand) > eps) {
		return E_ERROR;
	}
	answer = std::tgamma(operand + 1);

	delete parser_;
	return E_OK;
}

AbstractOperation* getOperation() {
	return new Factorial();
}