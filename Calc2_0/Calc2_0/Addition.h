#pragma once
#include <AbstractOperation.h>

class	Addition : public AbstractOperation {
private:
	const Associativity c_associativity = A_LEFT;
	const int c_priority = 1;
public:
	int getPriority() const;
	Associativity getAssociativity() const;
	ERROR_ count(const std::string&, double&);
	bool IsThatOp(const std::string&) const;
};