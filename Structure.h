#ifndef _STRUCTURE_H
#define _STRUCTURE_H
#include "General.h"


class StructureControle {
	public:
		StructureControle(InstructionV * instrv): instrv(instrv){}
		virtual ~StructureControle() {}	
		InstructionV* instrv;
};
class BlocIf : public StructureControle {
	public:
		BlocIf(Expression * expr, InstructionV * instrv):StructureControle(instrv), exprCondition(expr) {}
		Expression* exprCondition;
};

class BlocWhile : public StructureControle {
	public:
		BlocWhile(Expression * expr, InstructionV * instrv):StructureControle(instrv), exprCondition(expr) {}
		Expression* exprCondition;
};

class BlocFor : public StructureControle {
	public:
		BlocFor(Expression * exprInit, Expression * exprCondition, Expression * exprIncrementation, InstructionV * instrv):StructureControle(instrv), exprInit(exprInit), exprCondition(exprCondition), exprIncrementation(exprIncrementation) {}
		Expression* exprInit;
		Expression* exprCondition;
		Expression* exprIncrementation;
};


#endif
