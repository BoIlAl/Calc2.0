#pragma once
#include <stack> 
#include <string>
#include <Parser.h>
#include "OperationsMediator.h"

using namespace std;

enum OpNeighborType {
	ONT_NUMBER,
	ONT_OP_WITH_HIGH,
	ONT_OP_WITH_LOWER,
	ONT_EDGE_OF_EXPR
};

enum CALC_ERRORS {
	CE_DLLLOADER,
	CE_OPERATION,
	CE_PARSER,
	CE_OTHER,
	CE_OK
};

struct OpWithInfo {
	string operation;
	OpNeighborType right;
	OpNeighborType left;
};

class Calculator {
private:
	string string_;
	stack<double> numbers;
	stack<OpWithInfo*> operations_;
	OperationsMediator* opMediator_;
	Parser* parser_;

	int leftBracketCounter_;


	void freeAll();
	CALC_ERRORS collapseStack();
public:
	Calculator();

	CALC_ERRORS countTheString(const string&, double&);
	

	~Calculator();
};