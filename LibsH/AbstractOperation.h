#pragma once

#include <string>
#include <Parser.h>

	enum Associativity {
		A_LEFT,
		A_RIGHT,
		A_ERROR
	};

	enum ERROR_ {
		E_OK,
		E_ERROR
	};

	class AbstractOperation {
	protected:
		Parser* parser_ = nullptr;
	public:
		virtual int getPriority() const = 0;
		virtual Associativity getAssociativity() const = 0;

		virtual ERROR_ count(const std::string&, double&) = 0;
		virtual bool IsThatOp(const std::string&) const = 0;
	};