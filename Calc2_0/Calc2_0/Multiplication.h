#pragma once
#include <AbstractOperation.h>

class	Multiplication : public AbstractOperation {
private:
	const Associativity c_associativity = A_LEFT;
	const int c_priority = 2;
public:
	int getPriority() const;
	Associativity getAssociativity() const;
	ERROR_ count(const std::string&, double&) override;
	bool IsThatOp(const std::string&) const override;
};