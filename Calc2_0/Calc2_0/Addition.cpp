#include "Addition.h"

int Addition::getPriority() const {
	return c_priority;
}

Associativity Addition::getAssociativity() const {
	return c_associativity;
}

ERROR_ Addition::count(const std::string& expression, double& answer) {
	parser_ = new Parser(expression);

	int indOfOperation = 0;
	for (indOfOperation; indOfOperation < expression.size(); ++indOfOperation) {
		if (expression[indOfOperation] == '+') {
			if (indOfOperation == 0) {
				return E_ERROR;
			}

			break;
		}
		if (indOfOperation + 2 == expression.size()) {
			return E_ERROR;
		}
	}

	if (!parser_->isDigit(indOfOperation - 1)  
			|| !(parser_->isDigit(indOfOperation + 1) || parser_->isUnaryMinus(expression[indOfOperation + 1])) 
			|| !(parser_->isDigit(0) || parser_->isUnaryMinus(expression[0]))) {
		return E_ERROR;
	}

	int temp = 0;
	double first = parser_->findNumber(temp, true);
	if (temp != indOfOperation) {
		return E_ERROR;
	}

	temp = indOfOperation + 1;
	double second = parser_->findNumber(temp, true);
	if (temp != expression.size()) {
		return E_ERROR;
	}

	answer = first + second;

	delete parser_;
	return E_OK;
}

bool Addition::IsThatOp(const std::string& s) const {
	if (s == "+") {
		return true;
	}
	return false;
}
