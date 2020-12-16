#include "Calculator.h"


void Calculator::freeAll() {
	delete parser_;
	while (!operations_.empty()) {
		delete operations_.top();
		operations_.pop();
	}
	while (!numbers.empty()) {
		numbers.pop();
	}
}

CALC_ERRORS Calculator::collapseStack() {
	while (operations_.size()) {
		if (operations_.top()->operation == "(") {
			operations_.pop();
			return CE_OK;
		}
		

		string temp = std::to_string(numbers.top());
		numbers.pop();

		
		if (operations_.top()->left == ONT_EDGE_OF_EXPR) {
			temp = operations_.top()->operation + temp;
		}
		else if (operations_.top()->right == ONT_EDGE_OF_EXPR){
			temp = temp + operations_.top()->operation;
		}
		else if (operations_.top()->left == ONT_NUMBER) {
			if (operations_.top()->right == ONT_NUMBER || operations_.top()->right == ONT_OP_WITH_HIGH) {
				temp = std::to_string(numbers.top()) + operations_.top()->operation + temp;
				numbers.pop();
			}
			else if (operations_.top()->right == ONT_OP_WITH_LOWER) {
				temp = temp + operations_.top()->operation;
			}
		}
		else if (operations_.top()->right == ONT_NUMBER || operations_.top()->right == ONT_OP_WITH_HIGH) {
			temp = operations_.top()->operation + temp;
		}
		else {
			return CE_OTHER;
		}

		double answer = 0;
		if (opMediator_->count(operations_.top()->operation, temp, answer) == E_ERROR) {
			return CE_OPERATION;
		}
		numbers.push(answer);

		operations_.pop();
	}
	return CE_OK;
}

Calculator::Calculator() {
	opMediator_ = new OperationsMediator();
}

CALC_ERRORS Calculator::countTheString(const string& s, double& answer) {
	string_ = s;
	leftBracketCounter_ = 0;
	parser_ = new Parser(s);
	if (!opMediator_->loadAddingOps()) {
		freeAll();
		return CE_DLLLOADER;
	}

	bool opFlag = false;

	for (int ind = 0; ind < string_.size(); ++ind) {
		if (string_[ind] == ')') {
			--leftBracketCounter_;
			opFlag = false;
			if (leftBracketCounter_ < 0) {
				freeAll();
				return CE_OTHER;
			}
			else {
				collapseStack();
			}
		}
		else if (string_[ind] == '(') {
			leftBracketCounter_++;
			opFlag = false;
			if (operations_.size()) {
				operations_.top()->right = ONT_NUMBER;
			}
			operations_.push(new OpWithInfo{ "(", ONT_NUMBER, ONT_NUMBER });
		}
		else if (parser_->isDigit(ind)) {
			numbers.push(parser_->findNumber(ind, false));
			--ind;
			opFlag = false;
			if (operations_.size()) {
				operations_.top()->right = ONT_NUMBER;
			}
		}
		else {
			int tempInd = ind - 1;
			while (ind < string_.size() && !parser_->isDigit(ind) && string_[ind] != '(' && string_[ind] != ')') {
				++ind;
			} 
			--ind;

			OpWithInfo* currentOp = nullptr;

			while (ind != tempInd) {
				string tempOp = parser_->findOperation(ind, tempInd + 1);

				if (opMediator_->operationCheck(tempOp)) {

					if (!operations_.size() || operations_.top()->operation == "(") {
						if (tempInd + 1 == 0 || string_[tempInd] == '(') {
							currentOp = new OpWithInfo{ tempOp, ONT_EDGE_OF_EXPR, ONT_EDGE_OF_EXPR };
						}
						else {
							currentOp = new OpWithInfo{ tempOp, ONT_EDGE_OF_EXPR, ONT_NUMBER };
						}
					}
					else {
						int prevPrior = opMediator_->getPriority(operations_.top()->operation);
						int currPrior = opMediator_->getPriority(tempOp);

						if (prevPrior < currPrior || (prevPrior == currPrior && opMediator_->getAssociativity(operations_.top()->operation) == A_RIGHT)) {
							if (opFlag) {
								operations_.top()->right = ONT_OP_WITH_HIGH;
								currentOp = new OpWithInfo{ tempOp, ONT_EDGE_OF_EXPR, ONT_OP_WITH_LOWER };
							}
							else {
								currentOp = new OpWithInfo{ tempOp, ONT_EDGE_OF_EXPR, ONT_NUMBER };
							}
						}
						else {
							if (opFlag) {
								operations_.top()->right = ONT_OP_WITH_LOWER;
							}
							currentOp = new OpWithInfo{ tempOp, ONT_EDGE_OF_EXPR, ONT_NUMBER };

							CALC_ERRORS temp = collapseStack();
							if (temp != CE_OK) {
								freeAll();
								return temp;
							}
						}
					}

					operations_.push(currentOp);
					opFlag = true;
					break;
				}
				--ind;
			}
			if (!currentOp) {
				freeAll();
				return CE_OTHER;
			}
			ind = tempInd + operations_.top()->operation.size();
		}
	}
	if (opFlag) {
		operations_.top()->right = ONT_EDGE_OF_EXPR;
	}

	CALC_ERRORS temp = collapseStack();
	if (temp != CE_OK) {
		freeAll();
		return temp;
	}

	answer = numbers.top();
	numbers.pop();
	if (!operations_.empty()) {
		return CE_OTHER;
	}
	if (!numbers.empty()) {
		return CE_OTHER;
	}
	freeAll();
	return CE_OK;
}

Calculator::~Calculator() {
	delete opMediator_;
}
