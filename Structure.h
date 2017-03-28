#ifndef _STRUCTURE_H
#define _STRUCTURE_H
#include "General.h"
#include <iostream>

using namespace std;

class StructureControle : public InstructionV {
	public:
		StructureControle(InstructionV * instrv): instrv(instrv){}
		virtual ~StructureControle() {}	
		InstructionV* instrv;
		virtual void Afficher (){}
};
class BlocIf : public StructureControle {
	public:
		BlocIf(Expression * expr, InstructionV * instrv, InstructionV * blocElse = NULL):StructureControle(instrv), exprCondition(expr), blocElse(blocElse){}
		Expression* exprCondition;
		InstructionV * blocElse;
		void Afficher () {
			cerr<<"BLOC_IF ( "; exprCondition->Afficher(); cerr<<" ) {"<<endl;
			instrv->Afficher();
			cerr<<"}"<<endl;	
			if(blocElse!=NULL)
			{
				blocElse->Afficher();
			}
		}
};

class BlocWhile : public StructureControle {
	public:
		BlocWhile(Expression * expr, InstructionV * instrv):StructureControle(instrv), exprCondition(expr) {}
		Expression* exprCondition;
		void Afficher () {
			cerr<<"BLOC_WHILE ( "; exprCondition->Afficher(); cerr<<" ) {"<<endl;
			instrv->Afficher();
			cerr<<"}"<<endl;	
		}
};

class BlocFor : public StructureControle {
	public:
		BlocFor(Expression * exprInit, Expression * exprCondition, Expression * exprIncrementation, InstructionV * instrv):StructureControle(instrv), exprInit(exprInit), exprCondition(exprCondition), exprIncrementation(exprIncrementation) {}
		Expression* exprInit;
		Expression* exprCondition;
		Expression* exprIncrementation;
		void Afficher () {
			cerr<<"BLOC_FOR ( "; exprInit->Afficher(); cerr<<", "; exprCondition->Afficher(); cerr<<", "; exprIncrementation->Afficher(); cerr<<") {"<<endl;
			instrv->Afficher();
			cerr<<"}"<<endl;	
		}
};


#endif
