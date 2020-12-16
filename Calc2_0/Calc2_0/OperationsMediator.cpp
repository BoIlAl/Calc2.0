#include "OperationsMediator.h"

OperationsMediator::OperationsMediator() {
	loader_ = new DllLoader();

	AbstractOperation* temp = new Addition();
	operations_.push_back(temp);
	temp = new Multiplication();
	operations_.push_back(temp);
}

bool OperationsMediator::loadAddingOps() {
	return loader_->getDllOperations(operations_);
}

bool OperationsMediator::operationCheck(const std::string& op) {
	for (int i = 0; i < operations_.size(); ++i) {
		if (operations_[i]->IsThatOp(op)) {
			lastOp_ = operations_[i];
			lastOpName_ = op;
			return true;
		} 
	}
	return false;
}


int OperationsMediator::getPriority(const std::string& op) {
	if (op == lastOpName_) {
		return lastOp_->getPriority();
	}
	for (int i = 0; i < operations_.size(); ++i) {
		if (operations_[i]->IsThatOp(op)) {
			lastOp_ = operations_[i];
			lastOpName_ = op;
			return lastOp_->getPriority();
		}
	}
	return -1;
}

Associativity OperationsMediator::getAssociativity(const std::string& op) {
	if (op == lastOpName_) {
		return lastOp_->getAssociativity();
	}
	for (int i = 0; i < operations_.size(); ++i) {
		if (operations_[i]->IsThatOp(op)) {
			lastOp_ = operations_[i];
			lastOpName_ = op;
			return lastOp_->getAssociativity();
		}
	}
	return A_ERROR;
}

ERROR_ OperationsMediator::count(const std::string& op, const std::string& exp, double& answer) {
	if (op == lastOpName_) {
		return lastOp_->count(exp, answer);
	}
	for (int i = 0; i < operations_.size(); ++i) {
		if (operations_[i]->IsThatOp(op)) {
			lastOp_ = operations_[i];
			lastOpName_ = op;
			return lastOp_->count(exp, answer);
		}
	}
	return E_ERROR;
}

OperationsMediator::~OperationsMediator() {
	for (int i = 0; i < operations_.size(); ++i) {
		delete operations_[i];
	}
	delete lastOp_;
	delete loader_;
}
