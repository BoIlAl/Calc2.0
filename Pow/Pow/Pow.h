#pragma once

#include"pch.h"
#include <AbstractOperation.h>
#include <Parser.h>
#include <cmath>

#ifdef POW_EXPORTS
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif 
	EXPORT AbstractOperation* getOperation();

	class EXPORT Pow : public AbstractOperation {
	private:
		const Associativity c_associativity = A_RIGHT;
		const int c_priority = 3;
	public:
		int getPriority() const;
		Associativity getAssociativity() const;
		ERROR_  count(const std::string&, double&);
		bool IsThatOp(const std::string&) const;
	};

#ifdef __cplusplus
}
#endif 