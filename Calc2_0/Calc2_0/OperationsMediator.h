#pragma once

#include "Addition.h"
#include "Multiplication.h"
#include "DllLoader.h"
#include <vector>

class OperationsMediator  {
private:
	DllLoader* loader_ = nullptr;
	std::vector<AbstractOperation*> operations_;
	AbstractOperation* lastOp_ = nullptr;
	std::string lastOpName_ = "";
public:
	OperationsMediator();
	bool loadAddingOps();
	bool operationCheck(const std::string&);

	int getPriority(const std::string&);
	Associativity getAssociativity(const std::string&);
	ERROR_ count(const std::string&, const std::string&, double&);
	~OperationsMediator();
};